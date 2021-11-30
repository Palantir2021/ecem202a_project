#!/usr/bin/env python
# -*- coding:utf-8 -*-

import socket

ip_port = ('164.67.234.12', 8888)

sk = socket.socket()            # 创建套接字
sk.bind(ip_port)                # 绑定服务地址
sk.listen(5)                    # 监听连接请求
print('waiting for client...')
conn, address = sk.accept()     # 等待连接，此处自动阻塞
print("get client");
print(address);
conn.sendall('Hello!'.encode('utf-8'))
while True:     # 一个死循环，直到客户端发送‘exit’的信号，才关闭连接
    client_data = conn.recv(1024).decode('utf-8')      # 接收信息
    if client_data == "exit":       # 判断是否退出连接
        exit("end!")
    print("message from%s:%s" % (address, client_data))
    conn.sendall('message received!'.encode('utf-8'))    # 回馈信息给客户端
conn.close()    # 关闭连接