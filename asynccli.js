	
	function no_click(ev){
	if(!ev){
		var ev = window.event ;
	}
	ev.preventDefault();
	};
	
	function fsub(ev){
		no_click(ev);
		var valiue;
		if(tform){
			valiue = tform.value;
		}else if(!tform && document.getElementById("d")){
			tform = document.getElementById("d");
			valiue = tform.value;
		}
		var data = 'd=[TXT]: ' + valiue ;
		xhrSend('./service.php', data);
	};
	
	function esub(){
		var data1 = "d=1" ;
		xhrSend('./service.php', data1);
	};
	
	function enfill(text){
		if(displ){
			displ.innerHTML = text;
		}else if(!displ && document.getElementById("test_d")){
			displ = document.getElementById("test_d");
			displ.innerHTML = text;
		}
	};
		
	function createXHR(){
		var XHR ;
		if(window.XMLHttpRequest){
		    var XHR = new XMLHttpRequest() ;
		}else{ 
            if(window.ActiveXObject){
				var XHR = new ActiveXObject("Microsoft.XMLHTTP") ;
			}else{
				var XHR = false;
			}
		};    
		return XHR ;
	};

	function xhrSend(send_to, data){
		var xmlhttp = createXHR();
		if(xmlhttp){
			xmlhttp.open("POST", send_to, true) ;
			xmlhttp.setRequestHeader("Content-type", "application/x-www-form-urlencoded");
			xmlhttp.setRequestHeader("Content-length", data.length);
			xmlhttp.setRequestHeader("Connection", "close");
			xmlhttp.onreadystatechange = function (){
				if(xmlhttp.readyState === 4){		  
					if(xmlhttp.status === 200){
						if(data === "d=1"){
							var txt = xmlhttp.responseText ;
							enfill(xmlhttp.responseText);
						}else{
							;
						}
						xhr = null ;
					}
				}
			};
			xmlhttp.send(data) ;
		}
	};
