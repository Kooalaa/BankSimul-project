package com.astru43.atm_app

import androidx.appcompat.app.AppCompatActivity
import android.os.Bundle
import android.widget.Button
import android.widget.EditText
import com.astru43.atm_app.util.UtilPreferences

class AddToken : AppCompatActivity() {
    override fun onCreate(savedInstanceState: Bundle?) {
        super.onCreate(savedInstanceState)
        setContentView(R.layout.activity_add_token)

        setSupportActionBar(findViewById(R.id.toolbar2))
        val okButton:Button = findViewById(R.id.button2)
        okButton.setOnClickListener {
            val token = findViewById<EditText>(R.id.inputToken).text.toString()
            UtilPreferences.setToken(token, this)
            finish()
        }
    }
}