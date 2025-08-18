int64_t IOTC_Session_Read(int64_t sid, void *buf, int64_t size, int64_t timeout, int32_t flags)
{
    unsigned char lost = 0;
    unsigned char datatype = 0;
    void *guard = *__stack_chk_guard;
    int64_t ret = IOTC_Session_Read_Check_Lost_Data_And_Datatype(
        sid, buf, size, timeout, &lost, &datatype, flags, 0);

    if (ret == 0 && guard == *__stack_chk_guard)
        return ret;

    __stack_chk_fail();
    /* no return */
}
int64_t IOTC_sCHL_shutdown(int64_t ssl)
{
    int32_t *bio = tutk_third_BIO_get_data(tutk_third_SSL_get_rbio(ssl));
    int32_t ret;

    if (!bio[21])
    {
        ret = 0;
        bio[20] = 1;            /* mark shutdown requested */
    }
    else
    {
        int32_t tmp = tutk_third_SSL_shutdown(ssl);
        bio[22] = 1;            /* shutdown completed */
        ret = (tmp <= 0) ? tutk_third_SSL_get_error(ssl, tmp) : 0;
    }

    TUTK_LOG_MSG(0, "SCHL", 2,
                 "[%s] SID[%d] ChID[%d] ret[%d]",
                 "IOTC_sCHL_shutdown", bio[0], bio[1], ret);
    return translate_Error(ret, ssl);
}
