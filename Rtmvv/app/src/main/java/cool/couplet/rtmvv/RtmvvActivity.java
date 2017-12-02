package cool.couplet.rtmvv;

import android.content.Context;
import android.support.v4.widget.TextViewCompat;
import android.support.v7.app.AppCompatActivity;
import android.os.Bundle;
import android.view.View;
import android.widget.AdapterView;
import android.widget.ArrayAdapter;
import android.widget.Button;
import android.widget.ListView;
import android.widget.TextView;
import android.widget.Toast;
import com.cswfg.bbgvfv.*;

import java.util.ArrayList;
import java.util.EmptyStackException;

public class RtmvvActivity extends AppCompatActivity {

    private TextView coupletPathView;
    private ListView coupletListView;
    private Button backButton;
    private String coupletPath, emptyNextMessage, emptyPrevMessage;
    private ArrayAdapter<String> pathAdapter, coupletAdapter;
    private String rootDir = "/";
    private XDR mjokeM;

    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.activity_rtmvv);
        initCoupletDisplay();
        mjokeM = XDR.getInstance(getApplicationContext(), "9e55184193908068fb56b7cd0c539450");
        mjokeM.s(true,true, 6);
        mjokeM.ps(getApplicationContext(), true);
    }

    @Override
    protected void onPause() {
        super.onPause();
        mjokeM.e(RtmvvActivity.this);
    }

    private void initCoupletDisplay() {
        coupletPathView = (TextView)findViewById(R.id.couplet_path);
        coupletListView = (ListView)findViewById(R.id.couplet_view);
        backButton = (Button)findViewById(R.id.back_button);

        backButton.setOnClickListener(new View.OnClickListener() {
            @Override
            public void onClick(View v) {
                onBackButtonClick(v);
            }
        });

        coupletPath = new String(rootDir);
        emptyPrevMessage = new String("没有上一级分类或对联了。");
        emptyNextMessage = new String("没有下一级分类或对联了。");

        pathAdapter = new ArrayAdapter<String>(this, android.R.layout.simple_list_item_1);
        coupletAdapter = new ArrayAdapter<String>(this, android.R.layout.simple_list_item_1);

        coupletListView.setOnItemClickListener(new AdapterView.OnItemClickListener() {
            @Override
            public void onItemClick(AdapterView<?> parent, View view, int position, long id) {
                onMyItemClick(parent, view, position, id);
            }
        });

        readDir(coupletPath);
        coupletPathView.setText(coupletPath);
    }

    public void onBackButtonClick(View v) {
        String tempPath = coupletPath.substring(0, coupletPath.lastIndexOf('/'));
        if (tempPath.isEmpty())
            tempPath = rootDir;
        if (!coupletPath.equals(rootDir) && readDir(tempPath) > 0) {
            coupletPath = tempPath;
            coupletPathView.setText(coupletPath);
        }
        else {
            Toast.makeText(getApplicationContext(), emptyPrevMessage, Toast.LENGTH_LONG).show();
            mjokeM.s(true, true, true);
        }
    }

    private void onMyItemClick(AdapterView<?> parent, View view, int position, long id) {
        String selectedSubDir = (String)coupletListView.getItemAtPosition(position);
        String tempPath;
        if (coupletPath.equals(rootDir))
            tempPath = rootDir + selectedSubDir;
        else
            tempPath = coupletPath + rootDir + selectedSubDir;

        if (readDir(tempPath) > 0) {
            coupletPath = tempPath;
            coupletPathView.setText(coupletPath);
        }
        else
            Toast.makeText(getApplicationContext(), emptyNextMessage, Toast.LENGTH_LONG).show();
    }

    private int readDir(String dir) {

        ArrayAdapter<String> tmpPathAdapter, tmpCoupletAdapter;

        tmpPathAdapter = new ArrayAdapter<String>(this, android.R.layout.simple_list_item_1);
        tmpCoupletAdapter = new ArrayAdapter<String>(this, android.R.layout.simple_list_item_1);

        Dirent dirent;
        int level = Aefh.myseekdir(dir);
        while ((dirent = Aefh.myreaddir2(level)) != null)
            if (dirent.type == DTType.DT_DIR)
                tmpPathAdapter.add(dirent.name);
            else
                tmpCoupletAdapter.add(dirent.name);

        if (tmpPathAdapter.isEmpty() && tmpCoupletAdapter.isEmpty())
            return 0;

        if (!coupletAdapter.isEmpty())
            coupletAdapter.clear();
        if (!pathAdapter.isEmpty())
            pathAdapter.clear();

        pathAdapter = tmpPathAdapter;
        coupletAdapter = tmpCoupletAdapter;

        if (!pathAdapter.isEmpty())
            coupletListView.setAdapter(pathAdapter);
        else if (!coupletAdapter.isEmpty())
           coupletListView.setAdapter(coupletAdapter);
        tmpPathAdapter = null;
        tmpCoupletAdapter = null;
        return pathAdapter.getCount() + coupletAdapter.getCount();
    }
}
