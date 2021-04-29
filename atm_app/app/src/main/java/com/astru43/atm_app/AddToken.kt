package com.astru43.atm_app

import android.os.Bundle
import android.os.VibrationEffect
import android.os.Vibrator
import android.text.Editable
import android.widget.Button
import android.widget.EditText
import androidx.appcompat.app.AppCompatActivity
import androidx.camera.view.PreviewView
import androidx.core.widget.addTextChangedListener
import com.astru43.atm_app.util.CameraUtil
import com.astru43.atm_app.util.PrefUtil
import java.util.*
import java.util.concurrent.ExecutorService
import java.util.concurrent.Executors

class AddToken : AppCompatActivity() {

    private lateinit var previewView: PreviewView
    private lateinit var cameraExecutor: ExecutorService
    private lateinit var cameraUtil: CameraUtil

    override fun onCreate(savedInstanceState: Bundle?) {
        super.onCreate(savedInstanceState)
        setContentView(R.layout.activity_add_token)
        setSupportActionBar(findViewById(R.id.toolbar2))

        val token: EditText = findViewById(R.id.inputToken)
        val okButton: Button = findViewById(R.id.button2)
        okButton.setOnClickListener {
            PrefUtil.setToken(token.text.toString(), this)
            finish()
        }
        token.addTextChangedListener { text ->
            okButton.isEnabled =
                text?.length == 86 || text.toString().toUpperCase(Locale.ROOT) == "NULL"
        }

        previewView = findViewById(R.id.Preview_settings)
        cameraExecutor = Executors.newSingleThreadExecutor()
        cameraUtil = CameraUtil(this, previewView, cameraExecutor) { data ->
            val editableData = Editable.Factory().newEditable(data)
            if (token.text.toString() != data) {
                token.text = editableData
                val vibrator = getSystemService(VIBRATOR_SERVICE) as Vibrator
                if (vibrator.hasVibrator()) {
                    val vibrationEffect = VibrationEffect.createOneShot(1, 1)
                    vibrator.vibrate(vibrationEffect)
                }
            }
        }

        okButton.isEnabled = false
    }

    override fun onDestroy() {
        super.onDestroy()
        cameraExecutor.shutdown()
    }
}