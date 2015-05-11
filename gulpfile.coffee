gulp      = require 'gulp'
webserver = require 'gulp-webserver'

gulp.task 'webserver', ->
  gulp.src './'
    .pipe(webserver(
      livereload:       true
      directoryListing: true
      open:             true
    ))
