Ubuntu端口转发设置
1. 启动端口转发
Sudo vim /etc/sysctl.conf配置文件，将net.ipv4.ip_forward = 1注释放开，这样允许iptalbes FORWARD 开启IPV4转发。
执行 sysctl -p 来使更改生效。
2. 查看转发表
iptables -t nat -L -n --line-number


3. 删除已有的转发
iptables -t nat -D PREROUTING 2

4. 添加规则
sudo iptables -t nat -A PREROUTING -p tcp -d 10.97.109.59 --dport 9998 -j DNAT --to-destination 192.168.2.14:22

5. 启用
sudo ufw enable  && sudo ufw disable 

