package com.example.rfidmonitoringapp;

import android.app.Activity;
import android.content.Context;
import android.view.LayoutInflater;
import android.view.View;
import android.view.ViewGroup;
import android.widget.BaseAdapter;
import android.widget.TextView;

import org.w3c.dom.Text;

import java.util.ArrayList;

public class UserAdapter extends BaseAdapter {

    Activity mContext;
    ArrayList<User> userlist;
    public UserAdapter(Activity context, ArrayList<User> ulist){
        this.userlist = ulist;
        this.mContext = context;
    }
    @Override
    public int getCount() {
        return userlist.size();
    }

    @Override
    public Object getItem(int i) {
        return null;
    }

    @Override
    public long getItemId(int i) {
        return 0;
    }

    @Override
    public View getView(int i, View view, ViewGroup viewGroup) {
        LayoutInflater inflater = mContext.getLayoutInflater();
        View useritem = inflater.inflate(R.layout.useritem, null);
        TextView usertype = (TextView) useritem.findViewById(R.id.usertype);
        TextView usertag = (TextView) useritem.findViewById(R.id.tag);
        TextView usertime = (TextView) useritem.findViewById(R.id.time);

        if(i==0){ // for two rows if(position==0 || position==1)
            useritem.setBackgroundColor(useritem.getResources().getColor(R.color.maroon));
        }
        usertype.setText(userlist.get(i).getUsertype());
        usertag.setText(userlist.get(i).getTag());
        usertime.setText(userlist.get(i).getTime());

        return useritem;
    }
}

