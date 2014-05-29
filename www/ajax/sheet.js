var TAB_GLOBEL=true;	/*true:update Sheet;false:update row*/
var DEV_MOD_SUBMIT=false;	
var request_xmlHttp=null;

function call_submit(row,cgi_name)
{
	if(request_xmlHttp==null)
		request_ajax_init();
	var row_num='tr'+row;
	var rowId=document.getElementById(row_num);
	var devId=document.getElementById('devId_'+row_num);
	var inputId=document.getElementById('inputId_'+row_num);
	var inputId2=document.getElementById('inputId_'+row_num+'b');
	var selectId=document.getElementById('selectId_'+row_num);
	var switch_opt=get_select_value(selectId);
	var statId=document.getElementById('enableBoxId_'+row_num); 
	var enable_flg=(statId.checked==true)?'on':'off';
	var startTime = inputId.value;
	var endTime = inputId2.value;

	var url="../cgi-bin/"+cgi_name+".cgi?hub_id="+escape(row)+"&dev_name="+escape(devId.innerHTML)+"&inputVal="+escape(startTime)+"&inputVal2="+escape(endTime)+"&switch_opt="+escape(switch_opt)+"&enableBox="+escape(enable_flg);
	request_xmlHttp.open("GET",url,true);
	request_xmlHttp.onreadystatechange=updateSheet;
	request_xmlHttp.send(null);
	TAB_GLOBEL=false;
}
function call_sheet(cgi_name,tb_name)
{
	if(request_xmlHttp==null)
		request_ajax_init();
	var url="../cgi-bin/"+cgi_name+".cgi?tb_name="+escape(tb_name);
	request_xmlHttp.open("GET",url,true);
	request_xmlHttp.onreadystatechange=updateSheet;
	request_xmlHttp.send(null);
}
/* get device sheet */
function call_devlist()
{
	if(request_xmlHttp==null)
		request_ajax_init();
	var url="../cgi-bin/device_list.cgi";
	request_xmlHttp.open("GET",url,true);
	request_xmlHttp.onreadystatechange=updateDevices;
	request_xmlHttp.send(null);
}
/* submit devices modification  */
function call_devSubmit(row)
{
	if(request_xmlHttp==null)
		request_ajax_init();
	var dev_id=document.getElementById('dev_id'+row);
	var dev_name=document.getElementById('dev_name'+row);
	var dev_power=document.getElementById('dev_power'+row);
	var cmd=null;
	var del_box=document.getElementById('del_box'+row);

	if(del_box.checked==true)
		cmd='DEL';
	else
		cmd='MOD';

	var url="../cgi-bin/device_manage.cgi?cmd="+escape(cmd)+"&dev_id="+escape(dev_id.innerHTML)+"&dev_name="+encodeURI(dev_name.value)+"&dev_power="+escape(dev_power.value);
	request_xmlHttp.open("GET",url,true);
	request_xmlHttp.onreadystatechange=updateDevices;
	request_xmlHttp.send(null);
	DEV_MOD_SUBMIT=true;
}
/* submit devices register information */
function call_devReg()
{
	if(request_xmlHttp==null)
		request_ajax_init();
	var dev_id=document.getElementById('reg_dev_id');
	var dev_name=document.getElementById('reg_name');
	var dev_power=document.getElementById('reg_power');
	var url="../cgi-bin/device_manage.cgi?cmd="+escape('REG')+"&dev_id="+escape(dev_id.value)+"&dev_name="+encodeURI(dev_name.value)+"&dev_power="+escape(dev_power.value);
	request_xmlHttp.open("GET",url,true);
	request_xmlHttp.onreadystatechange=updateDevices;
	request_xmlHttp.send(null);
	hide_table();

}
/* update device list */
function updateDevices()
{
	if(request_xmlHttp.readyState==4)
	{
	  	var data=request_xmlHttp.responseText;	
		var dev_tb=document.getElementById('dev_tbId');
		if(data=='-1')
		{
			alert('提交失败!');
			return -1;
		}
		else if(DEV_MOD_SUBMIT == true)
		{
			alert('提交成功!');
			DEV_MOD_SUBMIT=false;
		}
		dev_tb.innerHTML=data;
	}
}
function updateSheet()
{
	if(request_xmlHttp.readyState==4)
	{
	  	var data=request_xmlHttp.responseText.split('&');	
		var sect=null;
		if(data==-1)
		{
			alert('提交更新失败!');	
		}
		else
		{
		for (var i = 0; i < data.length-1; i++) {
			sect = data[i].split('|');
			var tr_num='tr'+sect[0];	
			var dev_name=sect[1];
			var Lvalue=sect[2];
			var Rvalue=sect[3];
			var switch_opt=sect[4];
			var flag=sect[5];
			set_devname(tr_num,dev_name);
			switch_ctrl(tr_num,switch_opt);
			enable_box(tr_num,flag);
			change_color(tr_num);
			set_inputScope(tr_num,Lvalue,Rvalue);
		}
		if(TAB_GLOBEL==false)/* update row data */
		{
			alert('提交更新成功!');
			TAB_GLOBEL=true;
		}
		}
	}
}
/*show device register table*/
function show_table()
{
	var id_tb="<td><input id=\"reg_dev_id\"type=\"text\"></td>"
	var dev_name="<td><input id=\"reg_name\"type=\"text\"></td>"
	var dev_power="<td><input id=\"reg_power\"type=\"text\"></td>"
	var new_tb=document.getElementById('reg_id');
	var	tb_header="<tr><th>设备ID</th><th>设备名称</th><th>设备功率</th></tr>" 
	var ok_btn="<button type=\"button\"onclick=\"call_devReg()\">确定</button>"
	var cancel_btn="<button type=\"button\" onclick=\"hide_table()\">取消</button>"
	new_tb.innerHTML=tb_header+"<tr>"+id_tb+dev_name+dev_power+"</tr>"+ok_btn+cancel_btn;
}
/*hide device register table*/
function hide_table()
{
	var reg_id=document.getElementById('reg_id');
	reg_id.innerHTML="";
}
function set_devname(tr_num,dev_name)
{
	var devId=document.getElementById('devId_'+tr_num);	
	devId.innerHTML=dev_name;
}
function set_inputScope(tr_num,Lvalue,Rvalue)
{
	var inputId=document.getElementById('inputId_'+tr_num);
	var inputId2=document.getElementById('inputId_'+tr_num+'b');
	inputId.value=Lvalue;
	inputId2.value=Rvalue;
}
function add_date()
{
	var selectId=document.getElementById('selectId_date');
	var row = get_select_value(selectId);
	var inputId=document.getElementById('inputId_tr'+row);	
	var inputId2=document.getElementById('inputId_tr'+row+'b');	

	var startDate='/'+document.getElementById('inputId_'+'date1').value;
	var endDate='/'+document.getElementById('inputId_'+'date2').value;
	var startTime=inputId.value ;
	var endTime=inputId2.value ;
	if(!is_contain_date(startTime)) //not contain date
	{
		startTime += startDate;	
		inputId.value=startTime;
	}
	if(!is_contain_date(endTime)) //not contain date
	{
		endTime += endDate;	
		inputId2.value=endTime;
	}
}
function is_contain_date(str)
{
	if(str.indexOf('/') >= 0) //contain date
		return true;
	return false;
}
function remove_date()
{
	var selectId=document.getElementById('selectId_date');
	var row = get_select_value(selectId);

	var inputId=document.getElementById('inputId_tr'+row);	
	var inputId2=document.getElementById('inputId_tr'+row+'b');	
	var startTime=inputId.value ;
	var endTime=inputId2.value ;
	var filter;
	if(is_contain_date(startTime))
	{
		filter = startTime.split('/');
		startTime = filter[0];
		inputId.value=startTime;
	}
	if(is_contain_date(endTime))
	{
		filter = endTime.split('/');
		endTime = filter[0];
		inputId2.value=endTime;
	}
}
/* change color to green when the row is selected*/
function change_color(tr_num)
{
	row=document.getElementById(tr_num);
	boxrow=document.getElementById('enableBoxId_'+tr_num);
	inputId=document.getElementById('inputId_'+tr_num);
	inputId2=document.getElementById('inputId_'+tr_num+'b');
	selectId=document.getElementById('selectId_'+tr_num);

	if(boxrow.checked==true)
	{
		row.style.color='green';
		boxrow.style.color='green';
		inputId.style.color='green';
		inputId2.style.color='green';
		selectId.style.color='green';
		
	}
	else
	{
		row.style.color='gray';
		boxrow.style.color='gray';
		inputId.style.color='gray';
		inputId2.style.color='gray';
		selectId.style.color='gray';
	}
}
function switch_ctrl(tr_num,stat)
{
	selectId=document.getElementById('selectId_'+tr_num);	
	selectId.options[stat].selected=true;
}
function enable_box(tr_num,flag)
{
	boxId=document.getElementById('enableBoxId_'+tr_num);
	value=(flag=='on')?1:null;
	boxId.checked=value;
}
function request_ajax_init()
{
	try  
	{  
			/* non-IE browser*/
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
/* get the select box's value */
function get_select_value(selectId)
{
	var index=selectId.selectedIndex;
	var value=selectId.options[index].value;
	return value;
}
function clearInput(id){
	var inputId1=document.getElementById(id);
	var inputId2=document.getElementById(id+'b');
	inputId1.value="";
	inputId2.value="";
}
