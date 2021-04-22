package com.astru43.atm_app

import android.content.Intent
import android.os.Bundle
import android.util.Log
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

class MainActivity : AppCompatActivity() {
    override fun onCreate(savedInstanceState: Bundle?) {
        super.onCreate(savedInstanceState)
        setContentView(R.layout.activity_main)

        setSupportActionBar(findViewById(R.id.toolbar))

        val queue = Volley.newRequestQueue(this)

        val sendButton: Button = findViewById(R.id.button)
        sendButton.setOnClickListener {
            val inputId: EditText = findViewById(R.id.inputId)
            val url = "http://astru.ddns.net:8080/mobile/mobile/" + inputId.text.toString()

            val request = JsonObjectRequest(Request.Method.GET, url, null, { response ->
                val textView: TextView = findViewById(R.id.response)
                textView.text = "Response: %s".format(response)

                if (response.has("error")) {
                    Log.i("Response", response.toString())
                    if (response.getString("error") == "No such atm token")
                        textView.text = response.getString("error")
                } else {
                    val intent = Intent(this, AcceptLogin::class.java).putExtra(
                        "com.astru43.atm_app.ATM_TOKEN",
                        inputId.text.toString()
                    )
                    startActivity(intent)
                }
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