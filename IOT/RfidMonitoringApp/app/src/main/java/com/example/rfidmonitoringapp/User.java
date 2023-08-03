package com.example.rfidmonitoringapp;

import androidx.annotation.NonNull;

import java.text.ParseException;
import java.text.SimpleDateFormat;
import java.util.Date;

public class User{
    private String usertype, tag, time;

    public User(){

    }
    public User(String utype,String  tag,String time){
        this.usertype = utype;
        this.tag = tag;
        this.time = time;
    }
    public String getUsertype(){
        return this.usertype;
    }
    public String getTag(){
        return this.tag;
    }
    public String getTime(){
        return this.time;
    }
    public void setUsertype(String a){
        this.usertype = a;
    }
    public void setTag(String b){
        this.tag = b;
    }
    public void setTime(String c){
        this.time = c;
    }

}
