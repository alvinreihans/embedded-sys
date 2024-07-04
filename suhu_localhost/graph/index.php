
<!DOCTYPE HTML PUBLIC "-//W3C//DTD HTML 4.01//EN" "http://www.w3.org/TR/html4/strict.dtd">
<html>
	<head>
		<meta http-equiv="Content-Type" content="text/html; charset=utf-8">
		<title>Suhu Bandar Lampung</title>
		
		
		<!-- 1. Add these JavaScript inclusions in the head of your page -->
		<script src="https://ajax.googleapis.com/ajax/libs/jquery/3.3.1/jquery.min.js"></script>
		<script src="https://code.highcharts.com/stock/highstock.js"></script>
		<script src="https://code.highcharts.com/highcharts.js"></script>
		<script src="https://code.highcharts.com/modules/data.js"></script>
		<script src="https://code.highcharts.com/modules/exporting.js"></script>
		
		
		<!-- 2. Add the JavaScript to initialize the chart on document ready -->
		<script type="text/javascript">
    window.setTimeout("waktu()",1000);
    function waktu() {
        var tanggal = new Date();
        setTimeout("waktu()",1000);
        document.getElementById("jam").innerHTML = tanggal.getHours();
        document.getElementById("menit").innerHTML = tanggal.getMinutes();
        document.getElementById("detik").innerHTML = tanggal.getSeconds();
    }
</script>


		
		
		
		
		
		
		
		<script>
		var chart; // global
		
		/**
		 * Request data from the server, add it to the graph and set a timeout to request again
		 */
		function requestData() {
			$.ajax({
				url: 'live-server-data.php', 
				success: function(point) {
					var series = chart.series[0],
						series = chart.series[1],
						
						shift = series.data.length > 20; // shift if the series is longer than 20
		
					// add the point
					chart.series[0].addPoint([point[0], point[1]], true, shift);
					chart.series[1].addPoint([point[0], point[2]], true, shift);
						
						
					//chart.series[0].addPoint(eval(point), true, shift);
					//chart.series[1].addPoint(eval(point), true, shift);
					// call it again after one second
					setTimeout(requestData, 5000);	
				},
				cache: false
			});
		}
			
		$(document).ready(function() {
		//$('.render_here').each(function(){
			chart = new Highcharts.Chart({

				time: {
  				useUTC: false,
  				timezone: 'Asia/Jakarta',
  				},

				chart: {
					renderTo: 'container',
					defaultSeriesType: 'spline',
					events: {
						load: requestData
					}
				},
				title: {
					text: 'Real Time Sensor Suhu & Kelembapan: Bandar Lampung & Sekitarnya <br>'
				},
				xAxis: {
					type: 'datetime',
					useUTC: 'false' , 
					tickPixelInterval: 150,
					maxZoom: 20 * 1000
				},
				yAxis: {
					minPadding: 0.2,
					maxPadding: 0.2,
					title: {
						
                        text: "Nilai ",
						margin: 180
					}
				},
				series: [{
					name: 'Suhu ',
					data: [],
					dashStyle: 'longdash',
				    color: "#00FF00"
				},
					{name: 'Kelembapan ',
				   
					data: []
					
					
				}]
			});		
		});
		

		</script>
		

<script>
    // Function ini dijalankan ketika Halaman ini dibuka pada browser
    $(function(){
    setInterval(timestamp, 1000);//fungsi yang dijalan setiap detik, 1000 = 1 detik
    });
    
    //Fungi ajax untuk Menampilkan Jam dengan mengakses File ajax_timestamp.php
    function timestamp() {
    $.ajax({
    url: 'ajax_timestamp.php',
    success: function(data) {
    $('#timestamp').html(data);
    },
    });
    }
    </script>
	





		

	</head>
	
<style>
    #jam-digital{overflow:hidden; width:350px}
    #hours{float:left; width:100px; height:50px; background-color:#6B9AB8; margin-right:25px}
    #minute{float:left; width:100px; height:50px; background-color:#A5B1CB}
    #second{float:right; width:100px; height:50px; background-color:#FF618A; margin-left:25px}
    #jam-digital p{color:#FFF; font-size:36px; text-align:center; margin-top:4px}
</style>

<div align="center">
<body onLoad="waktu()">
    <div id="jam-digital" align="center">
        
        
        <div id="hours" align="center"><p id="jam"></p></div>
        <div id="minute" align="center"><p id="menit"></p></div>
        <div id="second" align="center"><p id="detik"></p></div>
    </div>
</table>
</body>
</div>

	<body>
		
		<!-- 3. Add the container -->
		<div id="container" style="width: 1200px; height: 600px; margin: 1 auto"></div>

		    
		
		
		</div>
	
	</body>
</html>
