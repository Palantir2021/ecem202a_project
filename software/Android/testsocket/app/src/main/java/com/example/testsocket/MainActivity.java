package com.example.testsocket;

import android.support.v7.app.AppCompatActivity;
import android.os.Bundle;
import android.view.View;
import android.widget.Button;
import android.widget.EditText;
import android.widget.TextView;

import java.io.DataInputStream;
import java.io.DataOutputStream;
import java.io.InputStream;
import java.io.OutputStream;
import java.io.PrintWriter;
import java.net.Socket;


public class MainActivity extends AppCompatActivity implements View.OnClickListener{
    StringBuffer msg=new StringBuffer();
    String getS=" ";
    String sendmsg;    //文本消息
    Socket mysocket;     //用Socket定义客户端对象
    Button send;            //发送按钮
    TextView textview;      //用于显示收发的字符串
    EditText editText;         //用于客户端输入字符串
    DataInputStream in;
    DataOutputStream outt;   //输入输出读写
    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.activity_main);
        //控件初始化
        send=(Button) findViewById(R.id.send);
        textview=(TextView) findViewById(R.id.textview);
        editText=(EditText) findViewById(R.id.editText);
        send.setOnClickListener(this);
        new Thread(new Runnable(){      //开启线程连接服务端
            @Override
            public void run() {
                try{
                    String ip="164.67.234.12";
                    mysocket=new Socket(ip,8888);   //服务端地址及端口
                    in=new DataInputStream(mysocket.getInputStream());

                    //输入输出流
                    while(true){

                        getS= "服务器："+in.readUTF()+"\n";   //读取输入流
                        msg.append(getS);
                        showmsg(msg.toString());      //输入显示更新在主界面

                    }


                }catch(Exception e){
                    System.out.println("wrong");
                    //错误
                }
            }
        }
        ).start();
    }
    private void showmsg(final String ms){   //必须在主线程中进行UI操作
        runOnUiThread(new Runnable(){
            @Override
            public void run() {
                textview.setText(ms);
            }
        });

    }

    @Override
    public void onClick(View v) {
        switch(v.getId()){
            case R.id.send:   //发送按钮

                sendmsg=editText.getText().toString()+"\n";   //获取客户端输入
                //getS="客户端:"+sendmsg;
                //msg.append(getS);
                //showmsg(msg.toString());
                //msg.append("客户端:"+sendmsg+"\n");
                try{
                    mysocket.close();
                    String ip="164.67.234.12";
                    mysocket=new Socket(ip,8888);   //服务端地址及端口
                    in=new DataInputStream(mysocket.getInputStream());
                    //showmsg("unsent");
                    //outt=new DataOutputStream(mysocket.getOutputStream());
                    //outt.writeUTF(sendmsg);
                    //DataOutputStream dout=new DataOutputStream(mysocket.getOutputStream());
                    //dout.writeUTF("Ok Boss");
                    //dout.flush();
                    //dout.close();
                    //showmsg("sent");
                    //mysocket.shutdownOutput();


                }catch(Exception e){

                }
                break;
            default:
                break;
        }

    }
}