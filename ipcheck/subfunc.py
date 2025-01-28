import nmap
import socket

def get_ip_range():
    local_ip = socket.gethostbyname(socket.gethostname())
    subnet = '.'.join(local_ip.split(".")[:-1]) +'.0/24'
    return subnet

def scan ():
    nm = nmap.PortScanner()
    ip_range = get_ip_range
    print(f"Procurando a rede:{ip_range}")
    nm.scan(hosts=ip_range,arguments="-sn")

    active_ips = []
    for host in nm.all_hosts():
        if nm[host].state == "up":
            active_ips.append(host)
    return active_ips


