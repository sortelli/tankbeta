gulp      = require 'gulp'
webserver = require 'gulp-webserver'
coffee    = require 'gulp-coffee'
concat    = require 'gulp-concat'
filter    = require 'gulp-filter'
uglify    = require 'gulp-uglify'
main_bf   = require 'main-bower-files'

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

gulp.task 'libs', ->
  gulp.src main_bf()
    .pipe filter '*.js'
    .pipe concat 'libs.min.js'
    .pipe uglify()
    .pipe gulp.dest 'app'

gulp.task 'watch', ->
  gulp.watch 'src/**/*.coffee*', ->
    gulp.run 'compile'

gulp.task 'build', ->
  gulp.run 'libs', 'compile'

gulp.task 'default', ->
  gulp.run   'webserver', 'compile', 'watch'
