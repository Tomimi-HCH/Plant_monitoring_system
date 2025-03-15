### ESP8266 AT指令

#### 一、初始化与系统控制
##### 1.1 AT指令测试  
   - 指令：`AT`  
   - 功能：测试模块是否正常响应  
   - 响应：`OK`  
##### 1.2 重启模块  
   - 指令：`AT+RST`  
   - 功能：重启ESP8266并加载Flash配置  
   - 响应：`OK`（随后模块重启）  
##### 1.3 查询版本信息  
   - 指令：`AT+GMR`  
##### 1.4 关闭回显  
   - 指令：`ATE0`  
   - 功能：禁止AT指令回显（提升数据传输效率）  
   - 开启回显：`ATE1`  

---

#### 二、Wi-Fi基础配置
##### 2.1 设置Wi-Fi模式  
   - 指令：`AT+CWMODE=<mode>`  
   - 参数：  
     - `1`：Station模式（连接路由器）  
     - `2`：SoftAP模式（作为热点）  
     - `3`：混合模式（同时作为Station和AP）  
   - 示例：  
     ```bash
     AT+CWMODE=1\r\n  # 设置为Station模式
     OK
     ```

##### 2.2 连接Wi-Fi热点  
   - 指令：`AT+CWJAP_CUR="SSID","PASSWORD"`  
   - 参数：  
     - `SSID`：Wi-Fi名称（支持中文需转义）  
     - `PASSWORD`：Wi-Fi密码  
   - 响应：  
     ```bash
     WIFI CONNECTED
     WIFI GOT IP
     OK
     ```
   - 注意：  
     - 特殊字符需转义（如`\`变为`\\`）  
     - 可通过`AT+CWJAP_CUR?`查询连接状态  

##### 2.3 扫描可用AP  
   - 指令：`AT+CWLAP`  
   - 响应：  
     ```bash
     +CWLAP:(3,"ESP_AP",-53,"5C:CF:7F:12:34:56",1,1,36)
     +CWLAP:(3,"HomeWiFi",-61,"18:FE:34:AB:CD:EF",6,1,36)
     OK
     ```
   - 参数说明：  
     - `3`：加密方式（WPA2_PSK）  
     - `-53`：信号强度（dBm）  

---

#### 三、网络连接与数据传输
##### 3.1 获取本地IP地址  
   - 指令：`AT+CIFSR`  
   - 响应：  
     ```bash
     +CIFSR:STAIP,"192.168.1.100"
     +CIFSR:STAMAC,"18:FE:34:97:D5:7B"
     OK
     ```

##### 3.2 建立TCP连接  
   - 指令：`AT+CIPSTART="TCP","IP","PORT"`  
   - 示例：  
     ```bash
     AT+CIPSTART="TCP","api.example.com",80\r\n
     CONNECT OK
     ```

##### 3.3 发送数据（普通模式）  
   - 指令：`AT+CIPSEND=<length>`  
   - 流程：  
     ```bash
     AT+CIPSEND=5\r\n  # 发送5字节数据
     > Hello          # 输入数据后自动发送
     SEND OK
     ```

---

#### 四、高级基础操作
##### 4.1 恢复出厂设置  
   - 指令：`AT+RESTORE`  
   - 功能：清除所有用户配置并重启  
   - 注意：需重新烧录固件恢复默认参数  

##### 4.2 设置UART波特率  
   - 临时设置：`AT+UART_CUR=115200,8,1,0,0`  
   - 保存设置：`AT+UART_DEF=115200,8,1,0,0`  
   - 参数：  
     - `115200`：波特率  
     - `8`：数据位  
     - `1`：停止位  
     - `0`：无校验  

##### 4.3 进入深度睡眠  
   - 指令：`AT+GSLP=<time>`  
   - 参数：`time`为睡眠时间（单位：毫秒）  
   - 示例：  
     ```bash
     AT+GSLP=1000\r\n  # 睡眠1秒后唤醒
     OK
     ```
---

#### 五、操作实例
##### 5.1 单连接TCP Client
```bash
# 步骤1：配置WiFi模式（Station+AP混合模式）
AT+CWMODE=3  
OK

# 步骤2：连接路由器
AT+CWJAP="Your_SSID","Your_PASSWORD"  
WIFI CONNECTED  
WIFI GOT IP  
OK

# 步骤3：查询本地IP
AT+CIFSR  
+CIFSR:STAIP,"192.168.1.100"  
OK

# 步骤4：建立TCP连接（服务器IP:192.168.1.100，端口:8080）
AT+CIPSTART="TCP","192.168.1.100",8080  
OK

# 步骤5：发送数据（4字节）
AT+CIPSEND=4  
> test  
SEND OK

# 步骤6：接收服务器数据
+IPD,4:test
```

##### 5.2 UDP传输

###### 5.2.1 固定远端UDP通信  

```bash
# 步骤1：配置WiFi模式（Station+AP混合模式）
AT+CWMODE=3  
OK

# 步骤2：连接路由器
AT+CWJAP="Your_SSID","Your_PASSWORD"  
WIFI CONNECTED  
WIFI GOT IP  
OK

# 步骤3：查询本地IP
AT+CIFSR  
+CIFSR:STAIP,"192.168.1.100"  
OK

# 步骤4：使能多连接
AT+CIPMUX=1  
OK

# 步骤5：建立UDP连接（远端IP:192.168.1.100，端口:8888，本地端口:1112）
AT+CIPSTART=0,"UDP","192.168.1.100",8888,1112,0  
OK

# 发送数据（7字节）
AT+CIPSEND=0,7  
> UDPtest  
SEND OK

# 接收数据
+IPD,0,7:UDPtest
```

######  5.2.2 可变远端UDP通信 
```bash
# 建立UDP连接（允许远端变更）
AT+CIPSTART="UDP","192.168.1.100",8888,1112,2  
OK

# 发送数据到新远端（IP:192.168.1.101，端口:1000）
AT+CIPSEND=7,"192.168.1.101",1000  
> NewData  
SEND OK
```

##### 5.3 透传模式
###### 什么是透传模式？
透传（Transparent Transmission）是ESP8266 AT指令中的一种高效数据传输模式，允许用户通过串口直接发送数据到目标服务器，无需每次手动指定数据长度或格式。
1. 自动数据转发  
   在透传模式下，ESP8266会将串口接收到的数据直接转发到已建立的TCP/UDP连接，无需额外指令控制。
2. 简化操作流程  
   传统模式需先通过`AT+CIPSEND=<length>`指定数据长度，而透传模式下只需输入数据即可发送。
3. 支持协议  
   - TCP单连接：仅支持单连接模式（`AT+CIPMUX=0`）。  
   - UDP：需配置固定远端（`AT+CIPSTART`最后参数为0）。
###### 注意事项
1. 数据长度限制  
   - 单次发送数据最大长度为2048字节，超出部分会被截断并提示`busy`。
2. 连接保持  
   退出透传后，TCP/UDP连接仍然保持，可通过`AT+CIPSEND`重新进入透传。
3. UDP透传限制  
   UDP透传仅支持固定远端模式（`AT+CIPSTART`最后参数为0），否则无法进入透传。
###### 典型应用场景
- 实时数据传输：传感器数据上报、远程控制指令等需高频交互的场景。  
- 简化协议处理：适合已封装好的数据格式，无需额外解析。  

通过透传模式，开发者可大幅简化数据传输逻辑，尤其适合需要高频、低延迟通信的物联网应用场景。

###### 5.3.1 TCP单连接透传  
```bash
# 步骤1：配置WiFi模式（Station+AP混合模式）
AT+CWMODE=3  
OK

# 步骤2：连接路由器
AT+CWJAP="Your_SSID","Your_PASSWORD"  
WIFI CONNECTED  
WIFI GOT IP  
OK

# 步骤3：查询本地IP
AT+CIFSR  
+CIFSR:STAIP,"192.168.1.100"  
OK

# 步骤4：建立TCP连接（服务器IP:192.168.1.100，端口:8080）
AT+CIPSTART="TCP","192.168.1.100",8080  
OK

# 步骤5 进入透传模式
AT+CIPMODE=1  
OK

# 步骤6 开始发送数据(每次只能发送2048字节)
AT+CIPSEND  
> 透传数据...  
+++  # 退出透传（需连续发送且无换行）

# 步骤7. 退出透传模式
AT+CIPMODE=0

# 步骤8. 断开 TCP 连接
AT+CIPCLOSE
```

在透传发送数据过程中，若识别到单独的一包数据“+++”，则退出透传发送。  
- 若使用键盘打字输入“+++”，可能因耗时过长，不被系统识别为连续的三个“+”。建议使用串口工具一次性发送“+++”，且注意不要携带空格、换行符等不可见字符。  
- 操作完成后，需至少间隔1秒，再发送下一条AT指令。  

❗ 注意： 
通过“+++”退出透传发送数据后，会回到正常AT指令模式。此时，TCP连接仍保持，可再次发送`AT+CIPSEND`指令，重新开启透传。

###### 5.3.2 UDP透传  
```bash
# 建立UDP连接并进入透传
AT+CIPSTART="UDP","192.168.1.100",8888,1112,0  
OK  
AT+CIPMODE=1  
OK

# 发送数据
AT+CIPSEND  
> UDP透传数据  
+++  # 退出透传
```

##### 5.4 多连接TCP服务器
```bash
# 使能多连接
AT+CIPMUX=1  
OK

# 启动TCP服务器（默认端口:333）
AT+CIPSERVER=1  
OK

# 客户端连接后发送数据（连接ID:0）
AT+CIPSEND=0,4  
> test  
SEND OK

# 接收客户端数据
+IPD,0,4:test
```

---

#### 六、 高级技巧与注意事项
##### 6.1 数据发送限制  
   - 单次发送数据最大长度：2048字节  
   - 超过长度时，系统自动截断并提示`busy`，剩余数据丢弃  

##### 6.2 透传模式退出  
   - 必须连续发送`+++`（无换行），且间隔小于1秒  
   - 退出后需等待1秒再发送新指令  

##### 6.3 连接超时处理  
   - TCP服务器默认超时时间：300秒（可通过`AT+CIPSTO`设置）  
   - 长时间无数据通信会自动断开连接  

##### 6.4 异常处理  
   - 指令无响应：检查波特率、接线和模块供电  
   - 连接失败：确认IP/端口正确性，检查防火墙设置  

---

> 注：本教程基于ESP8266_NONOS_SDK V3.0.1，部分指令可能因固件版本不同略有差异。建议使用`AT+GMR`确认当前固件版本。