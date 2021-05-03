package com.astru43.atm_app

import android.os.Bundle
import android.widget.Button
import androidx.appcompat.app.AppCompatActivity
import com.android.volley.Request
import com.android.volley.toolbox.JsonObjectRequest
import com.android.volley.toolbox.Volley
import com.astru43.atm_app.util.PrefUtil
import org.json.JSONObject

class AcceptLogin : AppCompatActivity() {
    override fun onCreate(savedInstanceState: Bundle?) {
        super.onCreate(savedInstanceState)
        setContentView(R.layout.activity_accept_login)

        setSupportActionBar(findViewById(R.id.toolbar3))

        val queue = Volley.newRequestQueue(this)
        val url = "http://astru.ddns.net:8080/mobile/mobile"
        val token = PrefUtil.getToken(this)

        val requestBody = JSONObject()
        requestBody.put("mobile_identification", token)
        requestBody.put("atm_token", intent.extras?.get("com.astru43.atm_app.ATM_TOKEN"))

        findViewById<Button>(R.id.cancel_btn).setOnClickListener {
            requestBody.put("accept_status", false)
            val request = JsonObjectRequest(Request.Method.POST, url, requestBody, {}, {})
            queue.add(request)
            finish()
        }
        findViewById<Button>(R.id.ok_btn).setOnClickListener {
            requestBody.put("accept_status", true)
            val request = JsonObjectRequest(Request.Method.POST, url, requestBody, {}, {})
            queue.add(request)
            finish()
        }
    }
}


/*

 */