package com.stu.gui;

import java.awt.*;
import javax.swing.*;

public class FrameTest {
	public static void main(String[] args) {
		EventQueue.invokeLater(() -> {
			var frame = new SimpleFrame();
			frame.setDefaultCloseOperation(JFrame.EXIT_ON_CLOSE);
			frame.setVisible(true);
		});

	}
}

class SimpleFrame extends JFrame {
	private static int DEFAULT_HEIGHT = 200;
	private static int DEFAULT_WIDTH = 300;

	public SimpleFrame() {
		setSize(DEFAULT_WIDTH, DEFAULT_HEIGHT);
	}
}
