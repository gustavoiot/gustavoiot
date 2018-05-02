console.log("Buscar historico");

var botaoAdicionar = document.querySelector("#buscar-historico");

botaoAdicionar.addEventListener("click", function () {
  console.log("Buscando historico ...");
  //XMLHttpRequest(); objeto javascript responsavel em fazer requisições http
  //XML responsavel por fazer o transporte de dados XML
  var xhr = new XMLHttpRequest();

  xhr.open("GET","http://35.231.119.5:3000/acesso/");

  xhr.addEventListener("load",function () {
  var erroAjax = document.querySelector("#erro-ajax");
    if(xhr.status == 200){

    erroAjax.classList.add("invisivel");
    var resposta = xhr.responseText;
    //console.log(typeof resposta);
    var historico = JSON.parse(resposta);

    historico.forEach(function (historico) {//historico é que passa no array historico
      adicionahistoricoNaTabela(historico);
    });
  }else{
      console.log(xhr.status);
      console.log(xhr.resposta);

      erroAjax.classList.remove("invisivel");


  });
  xhr.send();
});
