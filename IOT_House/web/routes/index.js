var express = require('express');
var router = express.Router();

var t1 = "sensor 1!";
var t1_v = "499";
/* GET home page. */
router.get('/', function(req, res, next) {
  // res.render('index', { title: 'Express22' });
  res.render('index', {
    title1: t1,
    value1: t1_v 
  });
});

module.exports = router;
