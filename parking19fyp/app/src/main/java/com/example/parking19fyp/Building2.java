package com.example.parking19fyp;

import androidx.annotation.NonNull;
import androidx.appcompat.app.AppCompatActivity;

import android.content.Intent;
import android.graphics.Color;
import android.os.Bundle;
import android.view.MenuItem;
import android.view.View;
import android.widget.Button;
import android.widget.TextView;
import android.widget.Toast;

import com.google.android.material.bottomnavigation.BottomNavigationView;
import com.google.firebase.database.DataSnapshot;
import com.google.firebase.database.DatabaseError;
import com.google.firebase.database.DatabaseReference;
import com.google.firebase.database.FirebaseDatabase;
import com.google.firebase.database.ValueEventListener;

public class Building2 extends AppCompatActivity {

    TextView text1, text2, text3, mainread;
    FirebaseDatabase db = FirebaseDatabase.getInstance();
    DatabaseReference node;
    DatabaseReference b2fnode, b2snode, b2tnode;
    Button b1, b2, b3, b4, b5, b6;

    private BottomNavigationView.OnNavigationItemSelectedListener mOnNavigationItemSelectedListener
            = new BottomNavigationView.OnNavigationItemSelectedListener() {

        @Override
        public boolean onNavigationItemSelected(@NonNull MenuItem item) {
            switch (item.getItemId()) {
                case R.id.home:
                    Intent k = new Intent(Building2.this, MainActivity.class);
                    startActivity(k);
                    return true;
                case R.id.building3:
                    Intent l = new Intent(Building2.this, build3.class);
                    startActivity(l);
                    return true;
                case R.id.building4:
                    Intent m = new Intent(Building2.this, build4.class);
                    startActivity(m);
                    return true;
            }
            return false;

        }
    };

    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.activity_building2);

        BottomNavigationView navigation = (BottomNavigationView) findViewById(R.id.navigation);
        navigation.setOnNavigationItemSelectedListener(mOnNavigationItemSelectedListener);

        text1 = (TextView) findViewById(R.id.STATUS21);
        text2 = (TextView) findViewById(R.id.STATUS22);
        text3 = (TextView) findViewById(R.id.STATUS23);
        b1 = (Button) findViewById(R.id.button1);
        b2 = (Button) findViewById(R.id.button2);
        b3 = (Button) findViewById(R.id.button3);
        b4 = (Button) findViewById(R.id.button4);
        b5 = (Button) findViewById(R.id.button5);
        b6 = (Button) findViewById(R.id.button6);
        mainread = (TextView) findViewById(R.id.FIREBASESTATUS);

        node = db.getReference("Car_parking");
        b2fnode = node.child("p4");
        b2snode = node.child("p5");
        b2tnode = node.child("p6");

        b2fnode.addValueEventListener(new ValueEventListener() {
            @Override
            public void onDataChange(DataSnapshot dataSnapshot) {
                String value1 = dataSnapshot.getValue().toString(); //load status
                String value;
                if (value1.equals("1")) {
                    value = "NOT PARKED";
                    text1.setBackgroundColor(Color.RED);
                    text1.setText(value);
                    b1.setEnabled(false);
                    b2.setEnabled(true);
                } else if (value1.equals("0")) {
                    value = "PARKED";
                    text1.setText(value);
                    text1.setBackgroundColor(Color.GREEN);
                    b1.setEnabled(true);
                    b2.setEnabled(false);
                }

//                text1.setAllCaps(true);
            }

            @Override
            public void onCancelled(DatabaseError error) {
                Toast.makeText(Building2.this, "Connection Error", Toast.LENGTH_LONG).show();
            }
        });
        b2snode.addValueEventListener(new ValueEventListener() {
            @Override
            public void onDataChange(DataSnapshot dataSnapshot) {
                String value1 = dataSnapshot.getValue().toString(); //load status
                String value;
                if (value1.equals("1")) {
                    value = "NOT PARKED";
                    text2.setBackgroundColor(Color.RED);
                    text2.setText(value);
                    b4.setEnabled(true);
                    b3.setEnabled(false);
                } else if (value1.equals("0")) {
                    value = "PARKED";
                    text2.setText(value);
                    text2.setBackgroundColor(Color.GREEN);
                    b3.setEnabled(true);
                    b4.setEnabled(false);
                }

//                text1.setAllCaps(true);
            }

            @Override
            public void onCancelled(DatabaseError error) {
                Toast.makeText(Building2.this, "Connection Error", Toast.LENGTH_LONG).show();
            }
        });
        b2tnode.addValueEventListener(new ValueEventListener() {
            @Override
            public void onDataChange(DataSnapshot dataSnapshot) {
                String value1 = dataSnapshot.getValue().toString(); //load status
                String value;
                if (value1.equals("1")) {
                    value = "NOT PARKED";
                    text3.setBackgroundColor(Color.RED);
                    text3.setText(value);
                    b6.setEnabled(true);
                    b5.setEnabled(false);
                } else if (value1.equals("0")) {
                    value = "PARKED";
                    text3.setText(value);
                    text3.setBackgroundColor(Color.GREEN);
                    b5.setEnabled(true);
                    b6.setEnabled(false);
                }

//                text1.setAllCaps(true);
            }

            @Override
            public void onCancelled(DatabaseError error) {
                Toast.makeText(Building2.this, "Connection Error", Toast.LENGTH_LONG).show();
            }
        });

        b2.setOnClickListener(new View.OnClickListener() {
            @Override
            public void onClick(View v) {
                int value = 4;
                node.child("parkCar").setValue(value);
                // Write data to Firebase
                Toast.makeText(Building2.this, "Data Sent", Toast.LENGTH_LONG).show();
            }
        });
        b1.setOnClickListener(new View.OnClickListener() {
            @Override
            public void onClick(View v) {
                int value = 4;
                node.child("getCar").setValue(value);
                // Write data to Firebase
                Toast.makeText(Building2.this, "Data Sent", Toast.LENGTH_LONG).show();
            }
        });

        b4.setOnClickListener(new View.OnClickListener() {
            @Override
            public void onClick(View v) {
                int value = 5;
                node.child("parkCar").setValue(value);
                // Write data to Firebase
                Toast.makeText(Building2.this, "Data Sent", Toast.LENGTH_LONG).show();
            }
        });
        b3.setOnClickListener(new View.OnClickListener() {
            @Override
            public void onClick(View v) {
                int value = 5;
                node.child("getCar").setValue(value);
                // Write data to Firebase
                Toast.makeText(Building2.this, "Data Sent", Toast.LENGTH_LONG).show();
            }
        });

        b6.setOnClickListener(new View.OnClickListener() {
            @Override
            public void onClick(View v) {
                int value = 6;
                node.child("parkCar").setValue(value);
                // Write data to Firebase
                Toast.makeText(Building2.this, "Data Sent", Toast.LENGTH_LONG).show();
            }
        });
        b5.setOnClickListener(new View.OnClickListener() {
            @Override
            public void onClick(View v) {
                int value = 6;
                node.child("getCar").setValue(value);
                // Write data to Firebase
                Toast.makeText(Building2.this, "Data Sent", Toast.LENGTH_LONG).show();
            }
        });

        DatabaseReference connectedRef = FirebaseDatabase.getInstance().getReference(".info/connected");
        connectedRef.addValueEventListener(new ValueEventListener() {
            @Override
            public void onDataChange(@NonNull DataSnapshot snapshot) {
                boolean connected = snapshot.getValue(Boolean.class);
                if (connected) {
                    mainread.setText("FIREBASE CONNECTED ");
                } else {
                    mainread.setText("FIREBASE CONNECTION FAILED");
                }
            }

            @Override
            public void onCancelled(@NonNull DatabaseError error) {

            }
        });
    }
}