#include <ESP8266WiFi.h>
#include <ESP8266WebServer.h>
ESP8266WebServer webServer(80);
char* ssid = "123456789";
char* pass = "123456789";
//=========Biến chứa mã HTLM Website==//
const char MainPage[] PROGMEM = R"=====(
  <!DOCTYPE html> 
  <html>
   <head> 
       <title>HOME PAGE</title> 
       <style> 
          body {text-align:center;}
          h1 {color:#003399;}
          a {text-decoration: none;color:#FFFFFF;}
          .bt_on {height:50px; width:100px; margin:10px 0;background-color:#FF6600;border-radius:5px;}
          .bt_off {height:50px; width:100px; margin:10px 0;background-color:#00FF00;border-radius:5px;}
       </style>
       <meta charset="UTF-8">
   </head>
   <body> 
      <h1>ESP8266 Web Server</h1> 
      <div>Trạng thái trên chân D1: <b><pan id="trangthaiD1"><pan></b></div>
      <div>
        <button class="bt_on" onclick="getdata('onD1')">ON</button>
        <button class="bt_off" onclick="getdata('offD1')">OFF</button>
      </div>
      <div>Trạng thái trên chân D2: <b><pan id="trangthaiD2"><pan></b></div>
      <div>
        <button class="bt_on" onclick="getdata('onD2')">ON</button>
        <button class="bt_off" onclick="getdata('offD2')">OFF</button>
      </div>
      <div id="reponsetext"></div>
      <script>
        //-----------Tạo đối tượng request----------------
        function create_obj(){
          td = navigator.appName;
          if(td == "Microsoft Internet Explorer"){
            obj = new ActiveXObject("Microsoft.XMLHTTP");
          }else{
            obj = new XMLHttpRequest();
          }
          return obj;
        }
        var xhttp = create_obj();
        
        //-----------Thiết lập dữ liệu và gửi request-------
        function getdata(url){
          xhttp.open("GET","/"+url,true); // Thiết lập dữ liệu phương thức get; đường dẫn url gửi lên sever
          xhttp.onreadystatechange = process;//nhận reponse --> kiểm tra response 
          xhttp.send();//gửi dữ liệu lên sever
        }
        //-----------Kiểm tra response--------------------
        function process(){
          if(xhttp.readyState == 4 && xhttp.status == 200){ //sever gửi dât về hoàn tất chưa
            //------Updat data sử dụng javascript----------
            ketqua = xhttp.responseText; //lấy giá trị trả về
            document.getElementById("reponsetext").innerHTML=ketqua;     
          }
        }
        //------------Kiểm tra trạng thái chân D1 D2------
        function getstatusD1D2(){
          xhttp.open("GET","getstatusD1D2",true);
          xhttp.onreadystatechange = process_json;
          xhttp.send();
        }
        //-----------Kiểm tra response-------------------------------
        function process_json(){
          if(xhttp.readyState == 4 && xhttp.status == 200){
            //------Update data sử dụng javascript-------------------
            var trangthaiD1D2_JSON = xhttp.responseText;
            var Obj = JSON.parse(trangthaiD1D2_JSON);
            document.getElementById("trangthaiD1").innerHTML = Obj.D1;
            document.getElementById("trangthaiD2").innerHTML = Obj.D2;
          }
        }
        //---Ham update duu lieu tu dong---
        setInterval(function() {
          getstatusD1D2();
        }, 1000); // sau 1tg sữ gửi 1 hàm lên sever
      </script>
   </body> 
  </html>
)=====";
//=========================================//
void setup() {
  pinMode(D1,OUTPUT);
  pinMode(D2,OUTPUT);
  digitalWrite(D1,HIGH);
  digitalWrite(D2,HIGH);
  WiFi.begin(ssid,pass);
  Serial.begin(9600);
  Serial.print("Connecting");
  while(WiFi.status()!=WL_CONNECTED){
    delay(500);
    Serial.print("...");
  }
  Serial.println(WiFi.localIP());

  webServer.on("/",mainpage);
  webServer.on("/onD1",on_D1);
  webServer.on("/offD1",off_D1);
  webServer.on("/onD2",on_D2);
  webServer.on("/offD2",off_D2);
  webServer.on("/getstatusD1D2",get_statusD1D2);
  webServer.begin();
}
void loop() {
  webServer.handleClient();
}
//==========Chương trình con=================//
void mainpage(){
  String s = FPSTR(MainPage);
  webServer.send(200,"text/html",s);
}
void on_D1(){
  digitalWrite(D1,LOW);
  webServer.send(200,"text/html","CHÂN D1 ĐÃ ON");
}
void off_D1(){
  digitalWrite(D1,HIGH);
  webServer.send(200,"text/html","CHÂN D1 ĐÃ OFF");
}
void on_D2(){
  digitalWrite(D2,LOW);
  webServer.send(200,"text/html","CHÂN D2 ĐÃ ON");
}
void off_D2(){
  digitalWrite(D2,HIGH);
  webServer.send(200,"text/html","CHÂN D2 ĐÃ OFF");
}
void get_statusD1D2(){
  String d1,d2;
  if(digitalRead(D1)==1){
    d1 = "OFF";
  }else{
    d1 = "ON";
  }
  if(digitalRead(D2)==1){
    d2 = "OFF";
  }else{
    d2 = "ON";
  }
  String s = "{\"D1\": \""+ d1 +"\",\"D2\": \""+ d2 +"\"}";
  webServer.send(200,"application/json",s);
}
