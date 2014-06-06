var request_xmlHttp=null;
/* call modify user information */
function call_updateUser()
{
	if(request_xmlHttp==null)
		request_ajax_init();
	var userId = document.getElementById('user');
	var emailId = document.getElementById('email');
	var passwdId = document.getElementById('passwd');
	if(passwd.value=='')
	{
		alert('请输入密码!');	
		return -1;
	}
	if(!isEmail(emailId.value))
	{
		alert("邮箱不合法！");
		return 1;
	}
	var url="../cgi-bin/update_user.cgi?name="+escape(userId.value)+"&passwd="+escape(passwdId.value)+"&email="+escape(emailId.value);
	request_xmlHttp.open("GET",url,true);
	request_xmlHttp.onreadystatechange=updateUser;
	request_xmlHttp.send(null);
}
/* call list user information */
function call_listUser()
{
	if(request_xmlHttp==null)
		request_ajax_init();
	var url="../cgi-bin/list_user.cgi";	
	request_xmlHttp.open("GET",url,true);
	request_xmlHttp.onreadystatechange=updatelistUser;
	request_xmlHttp.send(null);
}
function call_updatePasswd()
{
	if(request_xmlHttp==null)
		request_ajax_init();
	var user=document.getElementById('user');
	var new_passwdId=document.getElementById('new_passwd');
	var old_passwdId=document.getElementById('old_passwd');
	var re_passwdId=document.getElementById('re_passwd');
	if(user.value == '')
	{
		alert('用户名不能为空!');	
		return -1;
	}
	if(old_passwdId.value==''||new_passwdId.value == ''||re_passwdId.value == '')
	{
		alert('密码项都不能为空!');	
		return -1;
	}
	if(new_passwdId.value != re_passwdId.value)
	{
		alert('两次输入密码不匹配!');	
		return -1;
	}
	var url="../cgi-bin/update_passwd.cgi?name="+escape(user.value)+"&passwd="+escape(new_passwdId.value)+"&old_passwd="+escape(old_passwdId.value);
	request_xmlHttp.open("GET",url,true);
	request_xmlHttp.onreadystatechange=updatePasswd;
	request_xmlHttp.send(null);
}
function call_updateNet()
{
	if(request_xmlHttp==null)
		request_ajax_init();
	var ip = document.getElementById('ip');
	var netmask = document.getElementById('netmask');
	var gateway = document.getElementById('gateway');
	if(!isIPa(ip.value))
	{
		alert('ip地址不合法！');	
		return -1;
	}
	if(!isMask(netmask.value))
	{
		alert('子网掩码不合法');	
		return -1;
	}
	if(!isIPa(gateway.value))
	{
		alert('网关地址不合法!');	
		return -1;
	}
	var url="../cgi-bin/update_net.cgi?ip="+escape(ip.value)+"&netmask="+escape(netmask.value)+"&gateway="+escape(gateway.value);
	request_xmlHttp.open("GET",url,true);
	request_xmlHttp.onreadystatechange=updateNet;
	request_xmlHttp.send(null);

}
function call_listNet()
{
	if(request_xmlHttp==null)
		request_ajax_init();
	var url="../cgi-bin/list_net.cgi";	
	request_xmlHttp.open("GET",url,true);
	request_xmlHttp.onreadystatechange=updatelistNet;
	request_xmlHttp.send(null);
	
}
function call_listMQ2()
{
	if(request_xmlHttp==null)
		request_ajax_init();
	var url="../cgi-bin/list_MQ2.cgi";	
	request_xmlHttp.open("GET",url,true);
	request_xmlHttp.onreadystatechange=updatelistMQ2;
	request_xmlHttp.send(null);
}
function call_updateMQ2()
{
	if(request_xmlHttp==null)
		request_ajax_init();
	var MQ2=document.getElementById('MQ2');
	var boxId=document.getElementById('eBox');
	var enable='off';
	if(boxId.value==true)
	{
		enable='on';	
	}
	var url="../cgi-bin/update_MQ2.cgi?MQ2="+escape(MQ2.value)+"&enable="+escape(enable);
	request_xmlHttp.open("GET",url,true);
	request_xmlHttp.onreadystatechange=updateMQ2;
	request_xmlHttp.send(null);
}
function updateMQ2()
{
	if(request_xmlHttp.readyState==4)
	{
  		var ack=request_xmlHttp.responseText;	
		var data=ack.split(':');
		if(data[0]=='-1')
			alert('修改失败!');
		var MQ2 = document.getElementById('MQ2');
		var eBox = document.getElementById('eBox');
		MQ2.value=data[1];
		if(data[2]=="on")
			eBox.value=true;
		else
			eBox.value=false;
		alert('修改成功!');
	}
}
function updatelistMQ2()
{
	if(request_xmlHttp.readyState==4)
	{
  		var ack=request_xmlHttp.responseText;	
		var MQ2 = document.getElementById('MQ2');
		MQ2.value=ack;
	}
}
function updatelistNet()
{
	if(request_xmlHttp.readyState==4)
	{
  		var ack=request_xmlHttp.responseText;	
		var data=ack.split(":");
		var ip = document.getElementById('ip');
		var netmask = document.getElementById('netmask');
		var gateway = document.getElementById('gateway');
		ip.value=data[1];
		netmask.value=data[2];
		gateway.value=data[3];
	}
}
function updateNet()
{
	if(request_xmlHttp.readyState==4)
	{
  		var data=request_xmlHttp.responseText;	
  		var ack=request_xmlHttp.responseText;	
		var data=ack.split(":");
		var ip = document.getElementById('ip');
		var netmask = document.getElementById('netmask');
		var gateway = document.getElementById('gateway');
		if( data[0] == '0')
		{
			ip.value=data[1];
			netmask.value=data[2];
			gateway.value=data[3];
			alert('修改成功！');
		}
		else
			alert('修改失败!');
	}
}
function updatePasswd()
{
	if(request_xmlHttp.readyState==4)
	{
  		var data=request_xmlHttp.responseText;	
		var result=data.split(':');
		if( data == '0:0')
			alert('密码修改成功!');
		else if(result[0]== '-1')
			alert('旧密码错误!');
		else if(result[1] == '-2')
			alert('新密码修改失败!');
	}
}
function updateUser()
{
	
	if(request_xmlHttp.readyState==4)
	{
  	var data=request_xmlHttp.responseText;	
	var ack=data.split(':');
	var userId=document.getElementById('user');
	var emailId=document.getElementById('email');
	var passwd=document.getElementById('passwd');
	if(ack[0]=='-1')
	{
		alert('密码错误!');
		userId.value="";
		emailId.value="";
		return -1;
	}
	else if(ack[0]== '-2')
	{
		alert('修改失败!');
	}

	userId.value=ack[1];
	emailId.value=ack[2];
	passwd.value='';
	alert('修改成功!');
	}
}
function updatelistUser()
{
	
	if(request_xmlHttp.readyState==4)
	{
  	var data=request_xmlHttp.responseText;	
	var ack=data.split(':');
	var userId=document.getElementById('user');
	var emailId=document.getElementById('email');
	var passwd=document.getElementById('passwd');
	userId.value=ack[1];
	emailId.value=ack[2];
	passwd.value='';
	}
}
function isIPa(strIP) {
		var re=/^(\d+)\.(\d+)\.(\d+)\.(\d+)$/g
				if(re.test(strIP))
				{
						if( RegExp.$1 <256 && RegExp.$2<256 && RegExp.$3<256 && RegExp.$4<256) return true;
				}
		return false;
}
function isEmail(email)
{
		var re_email = new RegExp("^([a-zA-Z0-9]+[_|\_|.]?)*[a-zA-Z0-9]+@([a-zA-Z0-9]+[_|\_|.]?)*[a-zA-Z0-9]+.[a-zA-Z]{2,3}$");
		if(re_email.test(email))
				return true;
		else
				return false;
}
function isMask(mask)
{
		mask;
		var exp=/^(254|252|248|240|224|192|128|0)\.0\.0\.0|255\.(254|252|248|240|224|192|128|0)\.0\.0|255\.255\.(254|252|248|240|224|192|128|0)\.0|255\.255\.255\.(254|252|248|240|224|192|128|0)$/;
		var reg = mask.match(exp);
		if(reg==null)
		{
				return false; //"非法"
		}
		else
		{
				return true; //"合法"
		}
}
function request_ajax_init()
{
	try  
	{  
			request_xmlHttp=new XMLHttpRequest();  
	}  
	catch (e)  
	{  
		try  
		{  
			request_xmlHttp=new ActiveXObject("Msxml2.XMLHTTP");
		}  
		catch (e)  
		{  
			request_xmlHttp=new ActiveXObject("Microsoft.XMLHTTP");  
		}  
	}
}
function set_defaultNet()
{
	var ip = document.getElementById('ip');
	var netmask = document.getElementById('netmask');
	var gateway = document.getElementById('gateway');
	ip.value="192.168.1.8";
	netmask.value="255.255.255.0";
	gateway.value="192.168.1.1";
}
function set_defaultMQ2()
{
	var MQ2=document.getElementById('MQ2');
	MQ2.value='29';
}
function change_boxColor()
{
	var boxId = document.getElementById('eBox');
	var hint = document.getElementById('MQ2hint');
	var hint2 = document.getElementById('MQ2hint2');
	var comment = document.getElementById('Mcomment');
	if(boxId.checked==true)
	{
//		hint.style.color='yellow';
		hint2.style.color='yellow';
//		comment.style.color='green';
	}
	else
	{
//		hint.style.color='gray';
		hint2.style.color='gray';
//		comment.style.color='gray';
	}
}
function sendPasswd()	
{
		if(confirm("发送密码到邮箱?"))	
		{
			if(request_xmlHttp==null)
				request_ajax_init();

			var url="../cgi-bin/send_passwd.cgi";	
			request_xmlHttp.open("GET",url,true);
			request_xmlHttp.onreadystatechange=updatesendPasswd;
			request_xmlHttp.send(null);
		}
}
function updatesendPasswd()
{

	if(request_xmlHttp.readyState==4)
	{
  		var ack=request_xmlHttp.responseText;	
		if(ack=='0')
			alert('密码已发送!');
		else
			alert('发送失败！');
		window.location.href="login.html"
	}
}
