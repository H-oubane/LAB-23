package com.example.monjnidemo;

import androidx.appcompat.app.AppCompatActivity;

import android.graphics.Color;
import android.os.Bundle;
import android.widget.TextView;

public class MainActivity extends AppCompatActivity {

    // Nouvelles methodes natives de securite
    public native boolean estEnvironnementSuspect();

    // Methodes natives existantes
    public native String salutDeJNI();
    public native int factoriel(int n);
    public native String inverserChaine(String s);
    public native int sommeTableau(int[] values);

    static {
        System.loadLibrary("securite-lib");
    }

    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.activity_main);

        TextView tvStatut = findViewById(R.id.tvStatut);
        TextView tvSalutation = findViewById(R.id.tvSalutation);
        TextView tvCalcul = findViewById(R.id.tvCalcul);
        TextView tvInverse = findViewById(R.id.tvInverse);
        TextView tvTotal = findViewById(R.id.tvTotal);

        // Verification de securite
        boolean environnementSuspect = estEnvironnementSuspect();

        if (environnementSuspect) {
            tvStatut.setText("STATUT SECURITE : ENVIRONNEMENT SUSPECT DETECTE");
            tvStatut.setTextColor(Color.RED);
            tvSalutation.setText("Fonction native desactivee - securite");
            tvCalcul.setText("Calcul natif bloque");
            tvInverse.setText("Inversion desactivee");
            tvTotal.setText("Somme desactivee");
        } else {
            tvStatut.setText("STATUT SECURITE : ENVIRONNEMENT SAIN");
            tvStatut.setTextColor(Color.parseColor("#2E7D32"));
            tvSalutation.setText(salutDeJNI());

            int resultat = factoriel(10);
            tvCalcul.setText("Factoriel de 10 = " + resultat);

            String inverse = inverserChaine("JNI est puissant !");
            tvInverse.setText("Texte inverse : " + inverse);

            int[] nombres = {5, 15, 25, 35, 45};
            int somme = sommeTableau(nombres);
            tvTotal.setText("Somme du tableau = " + somme);
        }
    }
}