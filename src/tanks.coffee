$ ->
  $('#tankbetajs').html '<canvas id="tankbetajs_canvas"/>'

  canvas = new fabric.Canvas 'tankbetajs_canvas'
  fabric.Object.prototype.transparentCorners = false

  canvas.setHeight 480
  canvas.setWidth  640

  tank_width  = 20
  tank_height = 20

  tank1 = new fabric.Rect
    width:      tank_width
    height:     tank_height
    left:       20
    top:        230
    angle:      0
    fill:       'rgba(255,0,0,0.5)'
    selectable: false

  tank2 = new fabric.Rect
    width:      tank_width
    height:     tank_height
    left:       600
    top:        230
    angle:      0
    fill:       'rgba(0,255,0,0.5)'
    selectable: false

  canvas.add tank1, tank2
