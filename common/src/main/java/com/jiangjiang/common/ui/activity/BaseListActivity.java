package com.jiangjiang.common.ui.activity;

import android.os.Bundle;
import android.widget.FrameLayout;

import com.jiangjiang.common.R;
import com.jiangjiang.common.ui.helper.DialogHelper;
import com.jiangjiang.common.ui.helper.DialogHelperImpl;

import androidx.annotation.LayoutRes;
import androidx.annotation.Nullable;
import androidx.appcompat.app.AppCompatActivity;

/**
 * Date:  2020-01-19
 * Time:  14:43
 * Author: jianglong
 * -----------------------------
 * MISSION
 */
public abstract class BaseListActivity extends AppCompatActivity implements DialogHelper {
    protected FrameLayout rootView;
    private DialogHelper mDialogHelper;

    @Override
    protected void onCreate(@Nullable Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.common_base_activity_layout);
        rootView = findViewById(R.id.fl_content_container);
        getLayoutInflater().inflate(getLayoutRes(), rootView);
        initDialogHelper();
        initView();

    }

    protected void initDialogHelper() {
        mDialogHelper = new DialogHelperImpl(this);
    }

    protected void initView() {
        initTitleLayout();
    }

    protected void initTitleLayout() {

    }


    protected abstract @LayoutRes int getLayoutRes();


    @Override
    public void showLoadingDialog() {
        mDialogHelper.showLoadingDialog();
    }

    @Override
    public void dismissLoadingDialog() {
        mDialogHelper.dismissLoadingDialog();
    }

    @Override
    public void showLockableLoadingDialog(int msgId) {
        mDialogHelper.showLockableLoadingDialog(msgId);
    }

    @Override
    public void showLockableLoadingDialog() {
        mDialogHelper.showLockableLoadingDialog();
    }

    @Override
    public void showLoadingDialog(boolean isCancelable, int msgId) {
        mDialogHelper.showLoadingDialog(isCancelable, msgId);
    }

    @Override
    public void showLoadingDialog(int msgId) {
        mDialogHelper.showLoadingDialog(msgId);
    }

    @Override
    public boolean isLoadingDialogShowing() {
        return mDialogHelper.isLoadingDialogShowing();
    }
}