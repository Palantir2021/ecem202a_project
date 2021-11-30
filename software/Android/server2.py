# -*- coding: utf-8 -*-
"""
Created on Sun Nov 14 20:51:07 2021

@author: Jinchen Wu
"""

import jpysocket
import socket

ip_port = ('164.67.234.12', 8888)

sk = socket.socket()            # 创建套接字
sk.bind(ip_port)                # 绑定服务地址
sk.listen(5)                    # 监听连接请求
print('waiting for client...')
conn, address = sk.accept()     # 等待连接，此处自动阻塞
print("get client");
print(address);
hello = jpysocket.jpyencode("Hello!")
conn.send(hello)

while True:     # 一个死循环，直到客户端发送‘exit’的信号，才关闭连接
    
    #client_data = conn.recv(1024)     # 接收信息
    #client_data = jpysocket.jpydecode(client_data)
    inp = input("send information:").strip()
    if not inp:     # 防止输入空信息，导致异常退出
        continue
    inp = jpysocket.jpyencode(inp)
    conn.send(inp)
    #if client_data == "exit":       # 判断是否退出连接
    #    exit("end!")
    #print("message from%s:%s" % (address, client_data))
    #msgrec = jpysocket.jpyencode("message received!\r\n")
    #conn.send(msgrec)    # 回馈信息给客户端
    #print("messagesent")
conn.close()    # 关闭连接