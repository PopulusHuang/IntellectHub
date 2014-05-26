var request_xmlHttp=null;
function hello()
{
	alert('hello');
}
function call_updateUser()
{
	if(request_xmlHttp==null)
		request_ajax_init();
	var userId = document.getElementById('user');
	var emailId = document.getElementById('email');
	var passwdId = document.getElementById('passwd');
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
function call_listUser()
{
	if(request_xmlHttp==null)
		request_ajax_init();
	var url="../cgi-bin/list_user.cgi";	
	request_xmlHttp.open("GET",url,true);
	request_xmlHttp.onreadystatechange=updateUser;
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
	alert(data);
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
