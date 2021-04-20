package com.astru43.atm_app

import android.content.Intent
import android.os.Bundle
import android.view.Menu
import android.view.MenuInflater
import android.view.MenuItem
import android.widget.Button
import android.widget.EditText
import android.widget.TextView
import androidx.appcompat.app.AppCompatActivity
import com.android.volley.Request
import com.android.volley.toolbox.JsonObjectRequest
import com.android.volley.toolbox.Volley
import org.json.JSONObject

class MainActivity : AppCompatActivity() {
    override fun onCreate(savedInstanceState: Bundle?) {
        super.onCreate(savedInstanceState)
        setContentView(R.layout.activity_main)

        setSupportActionBar(findViewById(R.id.toolbar))

        val queue = Volley.newRequestQueue(this)
        val url = "http://astru.ddns.net:8080/mobile/mobile"

        val sendButton: Button = findViewById(R.id.button)
        sendButton.setOnClickListener {
            val token = UtilPreferences.getToken(this)
            val inputId: EditText = findViewById(R.id.inputId)
            val requestBody = JSONObject()
            requestBody.put("mobile_identification", token)
            requestBody.put("accept_status", true)
            requestBody.put("atm_token", inputId.text.toString())
            val request = JsonObjectRequest(Request.Method.POST, url, requestBody, { response ->
                val textView: TextView = findViewById(R.id.response)
                textView.text = "Response: %s".format(response.toString())
            }, { error ->
                val textView: TextView = findViewById(R.id.response)
                textView.text = error.localizedMessage
            })


            queue.add(request)
        }
    }

    override fun onCreateOptionsMenu(menu: Menu?): Boolean {
        super.onCreateOptionsMenu(menu)
        val inflater: MenuInflater = menuInflater
        inflater.inflate(R.menu.main_menu, menu)
        return true
    }

    override fun onOptionsItemSelected(item: MenuItem): Boolean {
        return when (item.itemId) {
            R.id.token -> {
                val intent = Intent(this, AddToken::class.java)
                startActivity(intent)
                true
            }
            else -> super.onOptionsItemSelected(item)
        }


    }
}