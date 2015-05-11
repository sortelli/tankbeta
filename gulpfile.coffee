gulp      = require 'gulp'
webserver = require 'gulp-webserver'
coffee    = require 'gulp-coffee'
concat    = require 'gulp-concat'

gulp.task 'webserver', ->
  gulp.src './'
    .pipe webserver
      livereload:       true
      directoryListing: true
      open:             true

gulp.task 'compile', ->
  gulp.src 'src/**/*.coffee'
    .pipe coffee    bare: true
    .pipe concat    'tankbetajs.js'
    .pipe gulp.dest 'app'

gulp.task 'default', ->
  gulp.run   'webserver', 'compile'
  gulp.watch 'src/**/*.coffee*', ->
    gulp.run 'compile'
