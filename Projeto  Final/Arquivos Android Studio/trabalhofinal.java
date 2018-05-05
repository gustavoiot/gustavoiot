package iot.cefetmg.br.trabalhofinal;

import android.support.v7.app.AppCompatActivity;
import android.os.Bundle;
import android.util.Log;
import android.view.View;
import android.widget.Button;
import android.widget.TextView;

import java.text.SimpleDateFormat;
import java.util.Calendar;
import java.util.HashMap;
import java.util.Map;

public class trabalhofinal extends AppCompatActivity {

    TextView historicoget;


    Button  botaomanual;

    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        Log.i("Tela principal", "Create");



        setContentView(R.layout.activity_trabalhofinal);

        historicoget = (TextView) findViewById(R.id.historicoget);
        GetAcesso req = new GetAcesso(historicoget);
        req.execute();


        botaomanual = (Button) findViewById(R.id.botaomanual);
        botaomanual.setOnClickListener(new View.OnClickListener() {
            @Override
            public void onClick(View v) {
                String abertura = "Manual";

                Map<String, String> postData = new HashMap<>();
                postData.put("abertura", abertura);

                Calendar c = Calendar.getInstance();
                SimpleDateFormat dateformat = new SimpleDateFormat("dd-MMM-yyyy hh:mm:ss");
                String datetime = dateformat.format(c.getTime());
                postData.put("time", datetime);

                PostAcesso post = new PostAcesso(postData);
                post.execute();
            }
            });
        }
    }