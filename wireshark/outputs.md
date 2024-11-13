# Investigating how Sidekick Chat Assitant works in the backend  
## Preliminary investigation using WireShark
Reference to wireshark.png  
![alt text for screen readers](wireshark-ss.png "Wireshark output from intercepting Binary Ninja Traffic")


packet 98: RST,ACK to end TCP connection (flaged red bcos there is no existing connection)  
packet 103-105: TCP 3 way handshake sequence btwn client and api server  
packet 107-109: TLS Handshake, 109 contains encryption setup  
packet 110-118: Application data exchange  
packet 119-141: Keep alive + Application data  

need to use MITM proxy to decrypt packets (burp suite)


