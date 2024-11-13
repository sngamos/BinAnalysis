# Investigating how Sidekick Chat Assitant works in the backend  
## Preliminary investigation using WireShark

![alt text for screen readers](wireshark-ss.png "Wireshark output from intercepting Binary Ninja Traffic")
This is the output from Wireshark after intercepting Network Traffic from binary ninja ELF application.    

### Analysis of Packet Log    
packet 98: RST,ACK to end TCP connection (flaged red bcos there is no existing connection)  
packet 103-105: TCP 3 way handshake sequence btwn client and api server  
packet 107-109: TLS Handshake, 109 contains encryption setup  
packet 110-118: Application data exchange  
packet 119-141: Keep alive + Application data  

### Conclusion and findings  
Need to use MITM proxy to decrypt packets (burp suite) + Set custom CA cert so that TLS encryption can be decrypted.  

## Setting up MITM
### Install Burp Suite
Download Burp Suite:
``` 
https://portswigger.net/burp/releases/professional-community-2024-9-5?requestededition=community&requestedplatform=
```
Run Burp Suite installer:
```
# allow permissions to run this shell script  
chmod +x burpsuite_community_linux_v2024_9_5.sh  
# Run install shell script  
./burpsuite_community_linux_v2024_9_5.sh
```
### Configuring Burp Suite  
Navigate to `Proxy` --> `Proxy Settings`
Under `Proxy listeners`, check that there is a port listening for traffic.  
You should see `127.0.0.1:8080` by default, indicating Burp Suite is listening to traffic passing through port 8080 on local device.  
Click `Edit` on this port  
Under `Request Handling`, enable `Support invisible proxying`
Click `Ok` to save
### Install proxychains
We need proxychains to forward the network traffic from Binja to port 8080 so that Burp Suite can capture the traffic  
Install proxychains:  
```
sudo apt install proxychains
```
Configure proxychains to forward traffic to port 8080:
```
cd /etc/  
sudo nano proxychains.conf
```
1. Comment out `proxy_dns`
2. Ensure `dynamic_chain` and `random_chain` are commented out, `strict_chain` is **NOT** commented out
3. At the bottom of the file, append `http 127.0.0.1 8080`  
4. Check that your proxychains.conf file is same as the one i have updloaded.  
### Configure Burp Suite CA certificate
We need Binja to use Burp Suite's CA certificate so that we can inspect and decrypt the network packets intercepted by Burp Suite
1. Export Burp Suite's CA Certificate: `Proxy` --> `Proxy Settings` --> `Proxy listeners` --> `Import/ export CA certificate` --> `Export Certificate in DER format` --> Save the CA certificate file as `cacert.der`  
2. Convert certificate to `.pem`: 
```
openssl x509 -inform DER -in cacert.der -out burp_cert.pem -text
sudo cp burp_cert.pem /usr/local/share/ca-certificates/burp_cert.crt
sudo update-ca-certificates
```
### Run Binary Ninja with proxychains
Navigate to where your Binary Ninja's ELF file is located
```
proxychains ./binaryninja
```
Open Burp Suite, under `Proxy` --> `Intercept`, turn on `Intercept Off` --> `Intercept On`  
Open a file in Binary Ninja, then in sidekick Chat Bot Assistant, enter a prompt.  
In Burp Suite Application you should see a Request created.  
Click `Forward` button on Burp Suite.  
Inspect the contents of the request by clicking on it.


## Examples or outputs
File: LevelsByMacaroni841  
Prompt: explain in detail what does this main function do
Function: main (Mem location: `000011c9`)
output:
```
POST /api/v2/notebooks/title HTTP/2
Host: api.sidekick.binary.ninja
User-Agent: python-requests/2.32.3
Accept-Encoding: gzip, deflate, br
Accept: */*
Connection: keep-alive
Client-Version: 2.0.176
Client-System: Linux
Client-Machine: x86_64
Client-Bn-Version: 4.1.5902
Client-Py-Version: 3.10.12
Api-Key: 995a7df7c7f64c3fb0e0ac8dc2397e67
Bn-License: a5e55caa28e50ca62a4cca0452020c56
Content-Length: 3269
Content-Type: application/json

{  
    "messages":  
    [  
        {  
            "role": "user",  
            "content": "explain in detail what does this main function do",  
            "address": 4553,  
            "il_type": "HLIL",  
            "timestamp": 1731483877,  
            "context_tag": null  
            },  
            {  
            "role": "function",  
            "content":  
            "{\"id\": \"call_XmmOIG7nQY5080MyoaGWiV9T\", \"name\": \"get_function_containing_address\", \"arguments\": {\"address\": \"0x11c9\", \"il_type\": \"HLIL\"}}",  
            "address": 4553,  
            "il_type": "HLIL",  
            "timestamp": 1731483885,  
            "context_tag": "call_XmmOIG7nQY5080MyoaGWiV9T"},  
            {  
            "role": "tool",  
            "content": "Below is the decompiled HLIL for the function which contains address 0x11c9:\n\n11c9 | int32_t main(int32_t argc, char** argv, char** envp)  \n11e4 | printf(\"Enter a string: \")\n11fc | char buf_1\n11fc | fgets(&buf_1, 0x28, __TMC_END__)\n1208 | int32_t rax_1 = strlen(&buf_1)\n1208 | \n1214 | if (rax_1 != 6)\n1420 |     puts(\"FAILURE-LVL-1: how long is your \u2026\")\n1214 | else\n1224 |     puts(\"\\n\\n\\nLevel 1 Pass: String lengt\u2026\")\n122f |     char var_47\n122f |     \n122f |     if (var_47 != 0x34)\n140f |         puts(\"FAILURE-LVL-2: Maybe the program\u2026\")\n122f |     else\n123f |         puts(\"Level 2 Pass: the character is a\u2026\")\n123f |         \n124a |         if (buf_1 != 0x33)\n13fe |             puts(\"I think if requires another char\u2026\")\n124a |         else\n125a |             puts(\"Level 2.5 Pass: You understand t\u2026\")\n1269 |             puts(\"you will be prompted to enter a \u2026\")\n1278 |             puts(\"The first key and the second key\u2026\")\n128c |             printf(\"Enter string #2: \")\n12a4 |             void buf\n12a4 |             fgets(&buf, 0x28, __TMC_END__)\n12a4 |             \n12be |             if (strlen(&buf) != rax_1)\n13ed |                 puts(\"The string length has to be the \u2026\")\n12be |             else\n130c |                 for (int32_t i = 0; i s<= 4; i += 1)\n12f1 |                     if (*(&buf + i) - 0x30 != ((&buf_1)[i] - 0x30) * 2)\n12fd |                         puts(\"FAILURE-LVL-2-Look through the l\u2026\")\n1302 |                         break\n1302 |                 \n1318 |                 puts(\"SUCCESS-LVL-3: You Did it! i hop\u2026\")\n1327 |                 puts(\"**i pray for the day crackmes.on\u2026\")\n1336 |                 puts(\"If you havent done it before thi\u2026\")\n1345 |                 puts(\"For the bonus section you need t\u2026\")\n1354 |                 puts(\"When ready type a letter then pr\u2026\")\n1368 |                 __isoc99_scanf(&data_2365)\n1368 |                 \n1374 |                 if (rax_1 != 0x1b39)\n13be |                     puts(\"FAILURE-LVL-BONUS: Forcing you t\u2026\")\n13cd |                     puts(\"Cutter is actually pretty good f\u2026\")\n13dc |                     puts(\"Wowza! https://www.megabeets.net\u2026\")\n1374 |                 else\n1380 |                     puts(\"SUCCESS-LVL-BONUS: Well damn you\u2026\")\n138f |                     puts(\"Should I make more of these?\")\n139e |                     puts(\"Probably not with the yanderedev\u2026\")\n13ad |                     puts(\"Bye! - saltedMacaroni841\")\n13ad | \n142b | return 0", "address": 4553, "il_type": "HLIL", "timestamp": 1731483885, "context_tag": "call_XmmOIG7nQY5080MyoaGWiV9T"}]}
```


