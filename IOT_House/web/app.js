var createError = require('http-errors');
var express = require('express');
var path = require('path');
var cookieParser = require('cookie-parser');
var logger = require('morgan');

// var indexRouter = require('./routes/index');
var usersRouter = require('./routes/users');

var app = express();

app.io = require('socket.io')();

// view engine setup
app.set('views', path.join(__dirname, 'views'));
app.set('view engine', 'hbs');

app.use(logger('dev'));
app.use(express.json());
app.use(express.urlencoded({ extended: false }));
app.use(cookieParser());
app.use(express.static(path.join(__dirname, 'public')));

// app.use('/', indexRouter);
app.use('/users', usersRouter);

// catch 404 and forward to error handler
// app.use(function(req, res, next) {
//   next(createError(404));
// });

// error handler
app.use(function(err, req, res, next) {
  // set locals, only providing error in development
  res.locals.message = err.message;
  res.locals.error = req.app.get('env') === 'development' ? err : {};

  // render the error page
  res.status(err.status || 500);
  res.render('error');
});

app.get('/', function(req, res, next) {
  // res.render('index', { title: 'Express22' });
  res.render('index', {
    title1: 'title',
    value1: 'value'
  });
});



const json = `{
  "led1" : 11,
  "led2" : 222,
  "led3" : 333
}`;



app.io.on('connection', function(socket){
  console.log('connected..');
  socket.on('disconnect', function () {
    console.log('disconnected..');
  })
  setInterval(() => {
    socket.emit('msg', json);
  }, 3000);
});

module.exports = app;
