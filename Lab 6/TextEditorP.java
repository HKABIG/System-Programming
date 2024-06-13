import javax.swing.*;
import java.awt.*;
import java.awt.event.ActionListener;
import java.awt.event.ActionEvent;
import java.io.*;

class TextEditorP extends JFrame{
    private JTextArea textArea;
    TextEditorP(){
        textArea = new JTextArea();
        setTitle("simple text editor");
        setSize(600,400);
        setDefaultCloseOperation(EXIT_ON_CLOSE);
        JScrollPane scrollPane = new JScrollPane(textArea);
        add(scrollPane,BorderLayout.CENTER);

        JMenuBar menuBar = new JMenuBar();
        setJMenuBar(menuBar);
        JMenu  fileMenu = new JMenu("File");
        JMenuItem newItem = new JMenuItem("new");
        JMenuItem saveItem = new JMenuItem("save");

        newItem.addActionListener(new ActionListener(){
            @Override
            public void actionPerformed(ActionEvent e){
                textArea.setText("");
            }
        });
        saveItem.addActionListener(new ActionListener() {
            @Override
            public void actionPerformed(ActionEvent e){
                JFileChooser fileChooser = new JFileChooser();
                int result = fileChooser.showSaveDialog(TextEditorP.this);
                if(result==fileChooser.APPROVE_OPTION){
                    File file = fileChooser.getSelectedFile();
                    try(BufferedWriter writer = new BufferedWriter(new FileWriter(file))){
                        textArea.write(writer);
                    }catch(IOException ex){
                        JOptionPane.showMessageDialog(TextEditorP.this,"Error saving the file");
                    }
                }
            }
        });

        fileMenu.add(newItem);
        fileMenu.add(saveItem);

        JMenu editMenu = new JMenu("Edit");
        JMenuItem copy = new JMenuItem("copy");
        JMenuItem paste = new JMenuItem("paste");
        JMenuItem delete = new JMenuItem("delete");

        copy.addActionListener(new ActionListener() {
            @Override
            public void actionPerformed(ActionEvent e){
                textArea.copy();
            }
        });
        paste.addActionListener(new ActionListener() {
            @Override
            public void actionPerformed(ActionEvent e){
                textArea.paste();
            }
        });
        delete.addActionListener(new ActionListener() {
            @Override
            public void actionPerformed(ActionEvent e){
                textArea.replaceSelection("");
            }
        });

        editMenu.add(copy);
        editMenu.add(paste);
        editMenu.add(delete);

        menuBar.add(fileMenu);
        menuBar.add(editMenu);
        setVisible(true);
    }
    public static void main(String args[]){
        new TextEditorP();
    }
}