$ ->
  $('#tankbetajs').html '<canvas id="tankbetajs_canvas"/>'

  canvas = new fabric.Canvas 'tankbetajs_canvas'
  fabric.Object.prototype.transparentCorners = false

  canvas.setHeight 480
  canvas.setWidth  640

  tank_width  = 20
  tank_height = 20

  tank1 = null
  tank2 = null

  new fabric.Image.fromURL 'tank1.png', (img) ->
    tank1 = img
    canvas.add img.set
      width:          tank_width
      height:         tank_height
      left:           40
      top:            220
      angle:          90
      fill:           'rgba(255,0,0,0.5)'
      selectable:     true
      tank_direction: 1

  new fabric.Image.fromURL 'tank2.png', (img) ->
    tank2 = img
    canvas.add img.set
      width:          tank_width
      height:         tank_height
      left:           600
      top:            240
      angle:          270
      fill:           'rgba(0,255,0,0.5)'
      selectable:     false
      tank_direction: 3

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

  turn_tank = (tank, offset) ->
    # See http://javascript.about.com/od/problemsolving/a/modulobug.htm
    tank.tank_direction = (((tank.tank_direction + offset) % 4) + 4) % 4
    tank.setAngle tank.tank_direction * 90

  move_tank = (key_up, key_right, key_down, key_left, tank) ->
    if key_right
      turn_tank tank, 1
    else if key_left
      turn_tank tank, -1
    else if key_up || key_down
      move = switch tank.tank_direction
        when 0 then key: 'top',  offset: -1
        when 1 then key: 'left', offset:  1
        when 2 then key: 'top',  offset:  1
        when 3 then key: 'left', offset: -1

      if key_down
        move.offset *= -1

      arg = {}
      arg[move.key] = tank[move.key] + move.offset
      tank.set arg

  check_keyboard = ->
    if tank1 and tank2
      move_tank keyboard.tank1_up,
                keyboard.tank1_right,
                keyboard.tank1_down,
                keyboard.tank1_left,
                tank1

      move_tank keyboard.tank2_up,
                keyboard.tank2_right,
                keyboard.tank2_down,
                keyboard.tank2_left,
                tank2

      canvas.renderAll()

    setTimeout check_keyboard, 10

  setTimeout check_keyboard, 10
