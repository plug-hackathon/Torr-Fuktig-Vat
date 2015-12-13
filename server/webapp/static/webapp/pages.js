window.addEventListener("load", function () {
  //var server = "http://188.226.137.177:8000/sensordata"
  var server = "http://localhost:8000/api/sensordata/";
  var oReq = new XMLHttpRequest();
  oReq.addEventListener("load", function (response) {
    var r = response.target.response;
    
    var json = JSON.parse(r);

    var data = {
        labels : ["46", "47", "48", "49", "50"],
        datasets : [
          {
            fillColor : "rgba(220,220,220,0.5)",
            strokeColor : "rgba(220,220,220,1)",
            pointColor : "rgba(220,220,220,1)",
            pointStrokeColor : "#fff",
            data: []
          },
          {
            fillColor : "rgba(151,187,205,0.5)",
            strokeColor : "rgba(151,187,205,1)",
            pointColor : "rgba(151,187,205,1)",
            pointStrokeColor : "#fff",
            data : []
          }
        ]
      };
      
      json.forEach(function (reading) {
        var moist = data.datasets[0].data;
        moist.push(reading.moised);
        var temp = data.datasets[1].data;
        temp.push(reading.temp_air);
      });


      var myNewChart = new Chart($("#canvas").get(0).getContext("2d")).Line(data)

  });

  oReq.open("GET", server);
  oReq.send();

});
