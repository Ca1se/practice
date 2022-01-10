import java.io.*;

import java.util.ArrayList;

import java.util.Scanner;



class User {

    private int id;

    private String studentId;

    private String name;



    public User(String id, String name) {

        this.id = Integer.valueOf(id);

        this.studentId = id;

        this.name = name;

    }



    public int getId() {

        return id;

    }



    public String getStudentId() {

        return studentId;

    }



    public String getName() {

        return name;

    }



    @Override

    public String toString() {

        return String.format("id: %d, studentId: %s, name: %s", id, studentId, name);

    }

}



public class Test {

    public static void question1() {

        Scanner scan = null;

        PrintWriter writer = null;

        try {

            scan = new Scanner(new File("a.txt"));

            writer = new PrintWriter(new File("b.txt"));

            while(scan.hasNext()) {

                writer.println(scan.nextLine() + ";");

            }

        }catch (FileNotFoundException e) {

            e.printStackTrace();

        }finally {

            if(scan != null)

                scan.close();

            if(writer != null)

                writer.close();

        }

    }



    public static ArrayList<User> question2() {

        Scanner scan = null;

        ArrayList<User> list = new ArrayList<>();

        try {

            scan = new Scanner(new File("b.txt"));

            String line = null, id = null, name = null;

            int ind;

            while(scan.hasNext()) {

                line = scan.nextLine();

                ind = line.indexOf(',');

                id = line.substring(0, ind);

                name = line.substring(ind + 1, line.length() - 1);

                list.add(new User(id, name));

            }

        }catch(FileNotFoundException e) {

            e.printStackTrace();

        }finally {

            if(scan != null)

                scan.close();

        }

        return list;

    }



    public static void question3(ArrayList<User> list) {

        for(var it: list) {

            System.out.println(it);

        }

    }



    public static void main(String[] args) {

        question1();

        var list = question2();

        question3(list);

    }

}