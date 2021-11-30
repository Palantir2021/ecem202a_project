#!/usr/bin/env python
# -*- coding:utf-8 -*-

import socket

ip_port = ('164.67.234.12', 8888)

s = socket.socket()     # 创建套接字

s.connect(ip_port)      # 连接服务器

server_reply = s.recv(1024).decode('utf-8')
print(server_reply)
while True:     # 通过一个死循环不断接收用户输入，并发送给服务器
    inp = input("send information:").strip()
    if not inp:     # 防止输入空信息，导致异常退出
        continue
    s.sendall(inp.encode())

    if inp == "exit":   # 如果输入的是‘exit’，表示断开连接
        print("end!")
        break

    server_reply = s.recv(1024).decode('utf-8')
    print(server_reply)

s.close()       # 关闭连接