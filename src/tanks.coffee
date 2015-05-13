$ ->
  $('#tankbetajs').html '<canvas id="tankbetajs_canvas"/>'

  canvas = new fabric.Canvas 'tankbetajs_canvas'
  fabric.Object.prototype.transparentCorners = false

  canvas.setHeight 480
  canvas.setWidth  640

  game_delay    = 10
  turn_delay    = 20
  tank_width    = 20
  tank_height   = 20
  bullet_width  = 10
  bullet_height = 10
  bullet_speed  = 2
  tank1         = null
  tank2         = null

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
      tank_turn_cnt:  0

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
      tank_turn_cnt:  0

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
    tank.tank_turn_cnt += 1
    if tank.tank_turn_cnt > turn_delay
      tank.tank_turn_cnt = 0
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
      tank.setCoords()

      move_back = false

      canvas.forEachObject (obj) ->
        if obj isnt tank and obj.intersectsWithObject tank
          move_back = true

      if move_back
        arg[move.key] = tank[move.key] - move.offset
        tank.set arg
        tank.setCoords()

  remove_bullet = (bullet) ->
    bullet.tank.tank_bullet = null
    canvas.remove bullet

  kill_tank = (bullet, tank) ->
    null

  move_bullet = (bullet) ->
    move = switch bullet.angle
      when   0 then key: 'top',  offset: -bullet_speed
      when  90 then key: 'left', offset:  bullet_speed
      when 180 then key: 'top',  offset:  bullet_speed
      when 270 then key: 'left', offset: -bullet_speed

    arg = {}
    arg[move.key] = bullet[move.key] + move.offset
    bullet.set arg
    bullet.setCoords()

    if bullet.intersectsWithObject tank1
      remove_bullet bullet
      kill_tank tank1
    else if bullet.intersectsWithObject tank2
      remove_bullet bullet
      kill_tank tank2
    else if bullet.left < 0 or bullet.left > 640 or bullet.top < 0 or bullet.top > 480
      remove_bullet bullet

  fire_bullet = (tank) ->
    pos = switch tank.angle
      when   0 then left: tank.left +  5, top: tank.top - 15, angle:   0
      when  90 then left: tank.left + 15, top: tank.top +  5, angle:  90
      when 180 then left: tank.left -  5, top: tank.top + 15, angle: 180
      when 270 then left: tank.left - 15, top: tank.top -  5, angle: 270

    tank.tank_bullet = new fabric.Rect
      width:      bullet_width
      height:     bullet_height
      left:       pos.left
      top:        pos.top
      angle:      pos.angle
      fill:       'rgba(255,0,0,0.5)'
      selectable: false
      tank:       tank

    canvas.add tank.tank_bullet

  update_bullets = ->
    bullet_1 = tank1.tank_bullet
    bullet_2 = tank2.tank_bullet

    if bullet_1
      move_bullet bullet_1
    else if keyboard.tank1_fire
      fire_bullet tank1

    if bullet_2
      move_bullet bullet_2
    else if keyboard.tank2_fire
      fire_bullet tank2

  update_game = ->
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

    update_bullets()

  game_loop = ->
    setTimeout game_loop, game_delay
    if tank1 and tank2
      update_game()
      canvas.renderAll()

  setTimeout game_loop, game_delay
