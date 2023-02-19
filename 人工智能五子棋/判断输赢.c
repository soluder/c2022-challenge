int check(int pawn[320][320])
{
    int left = 20;
    int right = 300;
    int bottom = 300;
    int top = 20;
    int width = 20;
    int count = 0;
    int flag = 0;
    int prepawn = *(pawn[20] + 20);
    //检查列
    count = 0;
    for (int i = left; i <= right; i += width)
    {
        for (int j = top; j <= bottom; j += width)
        {
            if (count == 5) 
            {  
                return flag;
            }
            if (*(pawn[i] + j) != 0 && *(pawn[i] + j) == prepawn)
            {
                count++;
                flag = *(pawn[i] + j);
            }
            else if (*(pawn[i] + j) != 0)
            {
                count = 1;
                prepawn = *(pawn[i] + j);
                
            }
            else if (*(pawn[i] + j) == 0)
            {
                count = 0;
                prepawn = *(pawn[i] + j);
            }
        }
        count = 0;
    }
    //检查行
    count = 0;
    for (int j = left; j <= right; j += width)
    {
        for (int i = top; i <= bottom; i += width)
        {
            if (count == 5)
            {
                return flag;
            }
            if (*(pawn[i] + j) != 0 && *(pawn[i] + j) == prepawn)
            {
                count++;
                flag = *(pawn[i] + j);
            }
            else if (*(pawn[i] + j) != 0)
            {
                count = 1;
                prepawn = *(pawn[i] + j);

            }
            else if (*(pawn[i] + j) == 0)
            {
                count = 0;
                prepawn = *(pawn[i] + j);
            }
        }
        count = 0;
    }
        //检查对角线上半部分
    count = 0;
    for (int m = left; m < right - 80; m += width)
    {
         for (int i = m,j=20; i <= right; i += width,j+=width)
        {
             if (count == 5)
            {
                return flag;
            }
             if (*(pawn[i] + j) != 0 && *(pawn[i] + j) == prepawn)
            {
                count++;
                flag = *(pawn[i] + j);
            }
            else if (*(pawn[i] + j) != 0)
            {
                count = 1;
                prepawn = *(pawn[i] + j);

            }
            else if (*(pawn[i] + j) == 0)
            {
                count = 0;
                  prepawn = *(pawn[i] + j);
            }


        }
        count = 0;
    }
    //检查对角线下半部分
    count = 0;
    for (int m=top+width;m<bottom-80;m+=width)
    {
        for (int i=20,j=m;i<=bottom;i+=width,j+=width)
        {
            if (count == 5)
            {
                return flag;
            }
            if (*(pawn[i] + j) != 0 && *(pawn[i] + j) == prepawn)
            {
                count++;
                flag = *(pawn[i] + j);
            }
            else if (*(pawn[i] + j) != 0)
            {
                count = 1;
                prepawn = *(pawn[i] + j);

            }
            else if (*(pawn[i] + j) == 0)
            {
                count = 0;
                prepawn = *(pawn[i] + j);
            }


        }
        count = 0;
    }
    //检查斜对角线上半部分
    count = 0;
    for (int m = right; m > left+ 80; m -= width)
    {
        for (int i = m, j = 20; i >= left; i -= width, j += width)
        {
            if (count == 5)
            {
                return flag;
            }
            if (*(pawn[i] + j) != 0 && *(pawn[i] + j) == prepawn)
            {
                count++;
                flag = *(pawn[i] + j);
            }
            else if (*(pawn[i] + j) != 0)
            {
                count = 1;
                prepawn = *(pawn[i] + j);

            }
            else if (*(pawn[i] + j) == 0)
            {
                count = 0;
                prepawn = *(pawn[i] + j);
            }


        }
        count = 0;
    }
    //检查斜对角线下半部分
    count = 0;
    for (int m =top+width; m < bottom- 80; m += width)
    {
        for (int i = 320, j = m; j <= bottom; i -= width, j += width)
        {
            if (count == 5)
            {
                return flag;
            }
            if (*(pawn[i] + j) != 0 && *(pawn[i] + j) == prepawn)
            {
                count++;
                flag = *(pawn[i] + j);
            }
            else if (*(pawn[i] + j) != 0)
            {
                count = 1;
                prepawn = *(pawn[i] + j);

            }
            else if (*(pawn[i] + j) == 0)
            {
                count = 0;
                prepawn = *(pawn[i] + j);
            }


        }
        count = 0;
    }
    return 0;
    }
