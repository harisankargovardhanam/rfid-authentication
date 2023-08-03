package com.example.rfidmonitoringapp;

import androidx.annotation.RequiresApi;
import androidx.appcompat.app.AppCompatActivity;
import com.pusher.pushnotifications.PushNotifications;

import android.os.Build;
import android.os.Bundle;
import android.util.Log;
import android.widget.ListView;

import com.google.firebase.database.DataSnapshot;
import com.google.firebase.database.DatabaseError;
import com.google.firebase.database.DatabaseReference;
import com.google.firebase.database.FirebaseDatabase;
import com.google.firebase.database.ValueEventListener;


import java.time.LocalDateTime;
import java.time.format.DateTimeFormatter;
import java.util.ArrayList;
import java.util.Collections;
import java.util.Comparator;
import java.util.Locale;

@RequiresApi(api = Build.VERSION_CODES.O)
public class MainActivity extends AppCompatActivity {

    static String pusherInstanceID = "your_pusher_instance_ID";
    static String pusherInterest = "your_pusher_interest";
    static String pattern = "yyyy-MM-dd HH:mm";
    static DateTimeFormatter dateFormat = DateTimeFormatter.ofPattern(pattern, Locale.ENGLISH);
    ArrayList<User> userlist = new ArrayList<>();
    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.activity_main);

        ListView listView = (ListView) findViewById(R.id.list);
        UserAdapter adapter = new UserAdapter(this, userlist);
        listView.setAdapter(adapter);

        PushNotifications.start(getApplicationContext(), pusherInstanceID);
        PushNotifications.addDeviceInterest(pusherInterest);

        DatabaseReference databaseReference = FirebaseDatabase.getInstance().getReference("Users");
        databaseReference.addValueEventListener(new ValueEventListener() {
            @Override
            public void onDataChange(DataSnapshot snapshot) {
                userlist.clear();
                for(DataSnapshot dataSnapshot : snapshot.getChildren()){
                    User user = dataSnapshot.getValue(User.class);
                    userlist.add(user);
                }
                Collections.sort(userlist, new Comparator<User>() {
                    @Override
                    public int compare(User user1, User user2) {
                        LocalDateTime date1 = null;
                        LocalDateTime date2 = null;
                        date1 = LocalDateTime.parse(user1.getTime(), dateFormat);
                        date2 = LocalDateTime.parse(user2.getTime(), dateFormat);
                        Log.e("date", String.valueOf(date1)+" "+String.valueOf(date2));
                        return date1.compareTo(date2);
                    }
                });
                Collections.reverse(userlist);
                adapter.notifyDataSetChanged();
            }

            @Override
            public void onCancelled(DatabaseError error) {

            }
        });

    }
}