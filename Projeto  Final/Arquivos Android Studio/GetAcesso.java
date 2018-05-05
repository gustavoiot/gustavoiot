package iot.cefetmg.br.trabalhofinal;

import android.os.AsyncTask;
import android.util.Log;
import android.widget.ListView;
import android.widget.TextView;

import org.json.JSONArray;
import org.json.JSONException;
import org.json.JSONObject;

import java.io.BufferedInputStream;
import java.io.BufferedReader;
import java.io.IOException;
import java.io.InputStream;
import java.io.InputStreamReader;
import java.net.HttpURLConnection;
import java.net.MalformedURLException;
import java.net.URL;





public class GetAcesso extends AsyncTask<Integer,String,String> {

    TextView historicoget;
    URL url;
    String retorno="";
    String time, abertura;

    public GetAcesso(TextView historicoget){
        this.historicoget = historicoget;
        try {
            this.url = new URL("http://35.231.119.5:3000/acesso");
        } catch (MalformedURLException e) {
            e.printStackTrace();
        }
    }

    @Override
    protected void onPreExecute(){
        Log.i("Tarefa 1 - status", "PreExecute");
        historicoget.setText("iniciando");
    }
    @Override
    protected String doInBackground(Integer... params) {
        Log.i("Tarefa 1 - status", "InBackground");

        try {
            HttpURLConnection urlConnection = (HttpURLConnection) url.openConnection();

            InputStream stream = new BufferedInputStream(urlConnection.getInputStream());
            BufferedReader bufferedReader = new BufferedReader(new InputStreamReader(stream));
            StringBuilder builder = new StringBuilder();

            String inputString;
            while ((inputString = bufferedReader.readLine()) != null) {
                builder.append(inputString);
            }

            JSONArray leitura = new JSONArray(builder.toString());


            for (int i = 0; i < leitura.length(); i++) {
                JSONObject c = leitura.getJSONObject(i);

                time = c.getString("time");
                abertura = c.getString("abertura");
                retorno += "Time: "+time + " - abertura: " + abertura + "\n";
            }

            urlConnection.disconnect();
        } catch (IOException | JSONException e) {
            e.printStackTrace();
        }


        return retorno;
    }
    @Override
    protected void onPostExecute(String retorno){
        Log.i("Tarefa 1 - status", "PostExecute");
        historicoget.setText(retorno);
    }

}