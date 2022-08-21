#include "config.h"

//服务器主程序，调用WebServer类实现Web服务器
int main(int argc, char *argv[])
{
    //需要修改的数据库信息,登录名,密码,库名
    string user = "root";
    string passwd = "root";
    string databasename = "tinywebserverdb";

    //命令行解析
    Config config;
    config.parse_arg(argc, argv);

    WebServer server;

    //初始化
    server.init(config.PORT, user, passwd, databasename, config.LOGWrite, 
                config.OPT_LINGER, config.TRIGMode,  config.sql_num,  config.thread_num, 
                config.close_log, config.actor_model);
    

    //日志
    server.log_write();

    //数据库
    server.sql_pool();

    //线程池
    server.thread_pool();

    //触发模式
    server.trig_mode();

    //监听                  //服务器程序通常需要处理三类事件：I/O事件，信号及定时事件。
    server.eventListen();//添加了listenfd读事件以及处理信号及定时事件的管道m_pipefd[2]的读事件

    //运行
    server.eventLoop();
    
    return 0;
}