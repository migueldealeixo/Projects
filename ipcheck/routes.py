from flask import Blueprint,request,jsonify
from .subfunc import scan_network,get_ip_details

main = Blueprint('main',__name__)

@main.route("/")
def home():
    return "Bem vindo"

@main.route('/main')
def scan():
    newtwork = request.args.get('network', default='192.168.1.0/24', type=str)
    active_ips = scan_network(newtwork)
    ip_details = [get_ip_details(ip) for ip in active_ips]
    return jsonify({"network": newtwork, "active_ips": ip_details})

