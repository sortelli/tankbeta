$ ->
  $('#tankbetajs').html '<canvas id="tankbetajs_canvas"/>'

  canvas = new fabric.Canvas 'tankbetajs_canvas'
  fabric.Object.prototype.transparentCorners = false

  canvas.setHeight 480
  canvas.setWidth  640

  tank_width  = 20
  tank_height = 20

  tank1 = new fabric.Rect
    width:          tank_width
    height:         tank_height
    left:           20
    top:            230
    angle:          0
    fill:           'rgba(255,0,0,0.5)'
    selectable:     false
    tank_direction: 1

  tank2 = new fabric.Rect
    width:          tank_width
    height:         tank_height
    left:           600
    top:            230
    angle:          0
    fill:           'rgba(0,255,0,0.5)'
    selectable:     false
    tank_direction: 3

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

  turn_right = (direction) ->
    (direction + 1) % 4

  turn_left = (direction) ->
    # See http://javascript.about.com/od/problemsolving/a/modulobug.htm
    (((direction - 1) % 4) + 4) % 4

  move_tank = (key_up, key_right, key_down, key_left, tank) ->
    if key_right
      tank.tank_direction = turn_right tank.tank_direction
    else if key_left
      tank.tank_direction = turn_left tank.tank_direction
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
