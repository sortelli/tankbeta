$(function() {
  $('#tankbetajs').html('<canvas id="tankbetajs_canvas"/>')

  var canvas = new fabric.Canvas('tankbetajs_canvas');
  fabric.Object.prototype.transparentCorners = false;

  canvas.setHeight(480);
  canvas.setWidth(640);

  var tank1 = new fabric.Rect({
    width: 20, height: 20, left: 20, top: 230, angle: 0,
    fill: 'rgba(255,0,0,0.5)'
  }); 

  var tank2 = new fabric.Rect({
    width: 20, height: 20, left: 600, top: 230, angle: 0,
    fill: 'rgba(0,255,0,0.5)'
  }); 

  canvas.add(tank1, tank2);
});
