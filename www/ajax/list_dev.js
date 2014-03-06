function list_dev(){
	var xmlhttp;
	if (window.XMLHttpRequest)
	{// code for IE7+, Firefox, Chrome, Opera, Safari
			xmlhttp=new XMLHttpRequest();
	}
	else
	{// code for IE6, IE5
			xmlhttp=new ActiveXObject("Microsoft.XMLHTTP");
	}
	xmlhttp.onreadystatechange=function()
	{
			if (xmlhttp.readyState==4 && xmlhttp.status==200)
			{
					document.getElementById("bulb").innerHTML=xmlhttp.responseText;
			}
	}
	xmlhttp.open("GET","../cgi-bin/show_dev.cgi",true);
	xmlhttp.send(null);
}
function refresh_dev(){
	list_dev();
	/* refresh device list every two minutes */
	setTimeout("refresh_dev()",2*60*1000);
}
