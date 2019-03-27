package mainApp;

import javafx.fxml.FXML;
import javafx.scene.control.ListView;
import javafx.scene.control.TextArea;
import javafx.scene.control.TextField;

public class ZumoController {
	PLabSerial btSerial;
	
	@FXML
	ListView<String> comList;
	@FXML
	TextField cmd;
	@FXML
	TextArea terminal;

	@FXML
	public void initialize() {
		btSerial = new PLabSerial();
		for (String s :btSerial.getPortNames()) {
			comList.getItems().add(s);
		}
	}
	
	
	public void selectPort(String portName, PLabSerial serial) {
		serial.closePort();
		serial.openPort(portName);
	}
	
	@FXML
	public void handleComListClick() {
		selectPort(comList.getSelectionModel().getSelectedItem(),btSerial);
		System.out.println("Connected to " + btSerial.getOpenPortName());
		try {
			Thread.sleep(2000);
		} catch (InterruptedException e) {
		}
	}
	
	@FXML
	public void handleSendClick() {
		btSerial.sendMessage(cmd.getText());
		if (terminal.getText().equals("")) {
			terminal.setText(cmd.getText());
		}else {
			terminal.setText(terminal.getText()+"\n"+cmd.getText());
			cmd.setText("");
		}
	}
	
	public static void main(String[] args) {
		
	}

}
