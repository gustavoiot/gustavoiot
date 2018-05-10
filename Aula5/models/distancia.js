/** Pós Graduação Internet das Coisas - CEFET-MG
	Disciplina: Programação para Sistemas de Computação
	Exemplo prático de RESTFul com NodeJS e MongoDB
	Modelo Distancia
 */
 
var mongoose = require('mongoose');
var Schema = mongoose.Schema;
var autoIncrement = require('mongoose-auto-increment'); 
var mongooseApiQuery = require('mongoose-api-query'); 

var DistanciaSchema = new Schema({
    time: String,
    valor: String
});

autoIncrement.initialize(mongoose.connection);
DistanciaSchema.plugin(autoIncrement.plugin, 'distancia');
DistanciaSchema.plugin(mongooseApiQuery); 
module.exports = mongoose.model('distancia', DistanciaSchema);
