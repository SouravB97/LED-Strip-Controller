const char index_html[] PROGMEM = R"rawliteral(

<!DOCTYPE HTML>
<html>
<head>
	<title>Led Strip Controller</title>
	<style>
		html {font-family: Arial; display: inline-block; text-align: center;}
		h2 {font-size: 2.3rem;}
		p {font-size: 1.9rem;}
		body {max-width: 400px; margin:0px auto; padding-bottom: 25px;}
		.slider { -webkit-appearance: none; margin: 14px; width: 360px; height: 25px; background: #FFD65C;
			outline: none; -webkit-transition: .2s; transition: opacity .2s;}
		.slider::-webkit-slider-thumb {-webkit-appearance: none; appearance: none; width: 35px; height: 35px; background: #003249; cursor: pointer;}
		.slider::-moz-range-thumb { width: 35px; height: 35px; background: #003249; cursor: pointer; } 
	</style>
	<meta name=\viewport\ content=\width=device-width, initial-scale=1.0\>
</head>
<body bgcolor=\#ffffff\><center>
	<h1 style=\color: white;\>LED STRIP CONTROLLER</h1>
  <form action=\\\\ method = \get\><table>
    <tr>
      <td>Colour (hex):</td>
      <td><input type = \text\ name=\colour\></input></td>
    </tr>
    </table>
  </form>
	<p>
		<label for="vol">Brightness:</label>
		<input type="range" onchange="updateSliderBrightness(this)" id="brightness_slider" min="0" max="255" value="%brightness%" step="1" class="slider">
		<span id="textSliderValue">%brightness%</span>
	</p>
	<br/><br/>
</center></body>
<script>
function updateSliderBrightness(element) {
  var sliderValue = document.getElementById("brightness_slider").value;
  document.getElementById("textSliderValue").innerHTML = sliderValue;
  console.log(sliderValue);
  var xhr = new XMLHttpRequest();
  xhr.open("GET", "/slider?value="+sliderValue, true);
  xhr.send();
}
</script>

</html>;


)rawliteral";
