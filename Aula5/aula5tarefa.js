/**
 * Pós Graduação Internet das Coisas - CEFET-MG Disciplina: Programação para
 * Sistemas de Computação Exemplo prático de RESTFul com NodeJS e MongoDB
 */

/* Módulos Utilizados */
var express = require('express'); 
var cors = require('cors'); 
var bodyParser = require('body-parser'); 
var Distancia = require('./models/distancia'); // Modelos definidos
var mongoose = require('mongoose');
var mqtt = require('mqtt');

require('mongoose-middleware').initialize(mongoose);

mongoose.connect("mongodb://localhost:27017/sensor");
var client = mqtt.connect('tcp://localhost'); //inicia o mqtt

var app = express(); // Cria o app com Express
var router = express.Router();

app.use(cors()); // liberar todos os do app acessos CORS
app.use(bodyParser.urlencoded({ 
	extended : true
})); 
app.use(bodyParser.json()); // configurações do body parser

client.on('connect', function () {
   	 client.subscribe('topic-iot-cefetmg'); //conecta e assina o tópico MQTT
});


client.on('message', function (topic, message) { //aguarda mensagem do tópico assinado MQTT 
	  console.log(topic.toString());
	  console.log(message.toString());
	  var payload       = message.toString();
	  var message_topic = topic.toString();
	  
	  var distancia = new Distancia();

	  var d = new Date();
	 
	  distancia.time = d.getFullYear() + "-"
		+ ("00" + (d.getMonth() + 1)).slice(-2) + "-"
		+ ("00" + (d.getDate())).slice(-2) + " "
		+ d.toLocaleTimeString();
	 
	  distancia.valor = payload;

		distancia.save(function(error) { // insere no db
			if (error)
				console.log(error);

			console.log("Inserido com Sucesso!")
		});
	
});

/* Rota para acompanhar as requisições */
router.use(function(req, res, next) {
	console.log('Entrou na rota ');
	next(); // continua na próxima rota
});

//GET /
router.get('/', function(req, res) {
	res.json({
		message : 'API - IoT'
	});
});

//GET /distancia
/*router.route('/distancia').get(function(req, res) {
	Distancia.find(function(err, distancia) {
		if (err)
			res.send(err);

		res.json(distancia);
	});
	console.log('GET /distancia');
});*/

//GET /distancia
router.route('/distancia').get(function(req, res) {
	var limit = parseInt(req.query._limit) || 20;
	var valor = req.query.valor || {$gte: 0};
	var sort = parseInt(req.query._sort) || -1;
	Distancia.
	find().
	where({ valor: valor }).
	limit(limit).
	sort({ _id: sort })
	.exec(function(err, distancia) {
		if (err)
			res.send(err);

		res.json(distancia);
	});
	console.log('GET /distancia');
});

router.route('/distancia/q').get(function(req, res) {
	Distancia.apiQuery(req.query).exec(function(err, distancia) {
		if (err)
			res.send(err);

		res.json(distancia);
	});
	console.log('GET /distancia/q');
});

//GET /distancia/recente
router.route('/distancia/recente').get(function(req, res) {
	var limit =  1;
	var sort  = -1;
	Distancia.
	find().
	limit(limit).
	sort({ _id: sort })
	.exec(function(err, distancia) {
		if (err)
			res.send(err);

		res.json(distancia);
	});
	console.log('GET /distancia/recente');
});

//GET /distancia/elevada
router.route('/distancia/elevada').get(function(req, res) {
	var limit = 10;
	var valor = {$gte: 30};
	var sort =  -1;
	
    Distancia.
	find().
	where({ valor: valor }).
	limit(limit).
	sort({ _id: sort })
	.exec(function(err, distancia) {
		if (err)
			res.send(err);

		res.json(distancia);
	});
    console.log('GET /distancia/elevada');
});


//GET /distancia/:id
router.route('/distancia/:id').get(function(req, res) {
	Distancia.findById(req.params.id, function(error, distancia) {
		if(error)
			res.send(error);

		res.json(distancia);
	});
	console.log('GET /distancia/:id');
});

/* POST /distancia {time:"..",valor:"..."} */
router.route('/distancia').post(function(req, res) {
	var distancia = new Distancia();

	distancia.time = req.body.time;
	distancia.valor = req.body.valor;

	client.publish('topic-iot-cefetmg',  distancia.valor); //MQTT: publica o valor da distancia no Tópico
	
	distancia.save(function(error) {
		if (error)
			res.send(error);

		res.json({
			message : 'distancia inserida e publicada!'
		});
	});
		
	console.log('POST /distancia');
});

//PUT /distancia/:id {time:"..",valor:"..."}
router.route('/distancia/:id').put(function(req, res) {
	Distancia.findById(req.params.id, function(error, distancia) {
		if(error)
			res.send(error);

		distancia.time = req.body.time;
		distancia.valor = req.body.valor;

		distancia.save(function(error) {
			if(error)
				res.send(error);
			res.json({ message: 'Distancia Atualizado!' });
		});
	});
	console.log('PUT /distancia/:id');
});

//DELETE /distancia/:id
router.route('/distancia/:id').delete(function(req, res) {
	Distancia.remove({
		_id: req.params.id
	}, function(error) {
		if(error)
			res.send(error);
		res.json({ message: 'Distancia excluída com Sucesso! '});
	});
	console.log('DELETE /distancia/:id');
});

app.use('/', router);

app.listen(3000);
console.log('Servidor executando.');
