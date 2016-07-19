<?php
class client{
	/*
	public function send_ctrl($c = 3){
		echo 'ctrl';
		$f = fsockopen('127.0.0.1', 25001, 0, '', $c);
		
		if(is_resource($f)){
			fwrite($f,'');
			fclose($f);
			return true;
		}else{
			return false;
		}
	}*/
	
	public function send_data($data = ''){
		$str = '';
		$f = fsockopen('127.0.0.1', 25000);
		stream_set_timeout($f, 0, 800);
		if(is_resource($f)):
			fwrite($f, $data);
			while(($c = fgetc($f)) !== false):
				$str .= $c;
			endwhile;
			fclose($f);
			return $str;
		else:
			return false;
		endif;
	}
}
?>
