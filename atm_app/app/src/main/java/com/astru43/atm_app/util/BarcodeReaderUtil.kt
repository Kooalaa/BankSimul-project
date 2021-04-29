package com.astru43.atm_app.util

import android.util.Log
import androidx.camera.core.ImageAnalysis
import androidx.camera.core.ImageProxy
import com.google.mlkit.vision.barcode.Barcode
import com.google.mlkit.vision.barcode.BarcodeScannerOptions
import com.google.mlkit.vision.barcode.BarcodeScanning
import com.google.mlkit.vision.common.InputImage

class BarcodeReaderUtil(val Listener: (barcodeString: String) -> Unit) : ImageAnalysis.Analyzer {

    @androidx.camera.core.ExperimentalGetImage
    override fun analyze(image: ImageProxy) {
        val imageMedia = image.image
        if (imageMedia != null) {
            val barcodeOptions = BarcodeScannerOptions.Builder()
                .setBarcodeFormats(Barcode.FORMAT_QR_CODE).build()

            val realImage = InputImage.fromMediaImage(imageMedia, image.imageInfo.rotationDegrees)

            val scanner = BarcodeScanning.getClient(barcodeOptions)
            scanner.process(realImage).addOnSuccessListener {
                for (barcode in it) {
                    when (barcode.valueType) {
                        Barcode.TYPE_TEXT -> {
                            Log.i("BarcodeRead", "Successfully read barcode data")
                            Listener(barcode.displayValue!!)
                        }
                    }
                }
            }.addOnFailureListener {
                Log.e("BarcodeRead", "Failed to read the barcode", it)
            }.addOnCompleteListener {
                image.close()
            }
        }
    }
}