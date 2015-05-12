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

  keyboard =
    tank1_left:  false
    tank1_up:    false
    tank1_right: false
    tank1_down:  false
    tank1_fire:  false

    tank2_left:  false
    tank2_up:    false
    tank2_right: false
    tank2_down:  false
    tank2_fire:  false

  code_to_key = (code) ->
    switch code
      when 83 then 'tank1_left'   # S
      when 69 then 'tank1_up'     # E
      when 70 then 'tank1_right'  # F
      when 67 then 'tank1_down'   # C
      when 68 then 'tank1_fire'   # D

      when 37 then 'tank2_left'   # Left arrow
      when 38 then 'tank2_up'     # Up arrow
      when 39 then 'tank2_right'  # Right arrow
      when 40 then 'tank2_down'   # Down arrow
      when 13 then 'tank2_fire'   # Enter

  $(document).keydown (e) ->
    key = code_to_key e.which
    keyboard[key] = true

  $(document).keyup (e) ->
    key = code_to_key e.which
    keyboard[key] = false

  check_keyboard = ->
    if keyboard['tank1_up']
      tank1.set
        left: tank1.left + 1
      tank1.setCoords()
      console.log '' + tank1.left + ',' + tank1.getLeft()
    canvas.renderAll()
    setTimeout check_keyboard, 10

  setTimeout check_keyboard, 10
