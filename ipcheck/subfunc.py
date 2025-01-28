import subprocess
import requests
import ipaddress

def scan_network(network):
    active_ips = []
    for ip in ipaddress.IPv4Network(network, strict=False):
        result = subprocess.run(['ping', '-c', '1','-W', '1', str(ip)], stdout=subprocess.DEVNULL)
        if result.returncode == 0:
            active_ips.append(str(ip))
    return active_ips

def get_ip_details(ip):
    response = requests.get(f'https://ipinfo.io/{ip}/json')
    return response.json if response.status_code == 200 else {"error":"Falha na procuração de dados"}