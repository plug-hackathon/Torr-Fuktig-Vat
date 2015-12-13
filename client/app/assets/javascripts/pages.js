window.addEventListener("load", function () {
  console.log("load");

  var server = "http://188.226.137.177:8000/sensordata"
  var oReq = new XMLHttpRequest();
  oReq.addEventListener("load", function (response) {
    console.log(response);
    
    var data = {
        labels : ["46", "47", "48", "49", "50"],
        datasets : [
          {
            fillColor : "rgba(220,220,220,0.5)",
            strokeColor : "rgba(220,220,220,1)",
            pointColor : "rgba(220,220,220,1)",
            pointStrokeColor : "#fff",
            data : [65,59,90,81,56,55,40]
          },
          {
            fillColor : "rgba(151,187,205,0.5)",
            strokeColor : "rgba(151,187,205,1)",
            pointColor : "rgba(151,187,205,1)",
            pointStrokeColor : "#fff",
            data : [28,48,40,19,96,27,100]
          }
        ]
      };

      var myNewChart = new Chart($("#canvas").get(0).getContext("2d")).Line(data)

  });

  oReq.open("GET", server);
  oReq.send();

});
